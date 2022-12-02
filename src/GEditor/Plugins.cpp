#include "Plugins.hpp"
#include "GEditor/GEditor.hpp"
#include "Widgets/Label.hpp"
#include <cstring>
#include <filesystem>
#include <dlfcn.h>
#include <cxxabi.h>
#include <unistd.h>

booba::ApplicationContext* booba::APPCONTEXT = nullptr;
static const char* MODULES_DIRECTORY = "./modules/";

namespace mge {

    [[maybe_unused]] static void dmgl(const char* str)
    {
        char* name = nullptr;
        size_t len = 0;
        int res = 0;
        const char* thename = str;
        name = abi::__cxa_demangle(thename, name, &len, &res);
        if(res || !name)
        {
            mError << "Error: demangling returned " << res << mlg::endl;
            return;
        }
        mInfo << "Demangled: " << name << mlg::endl;
        free(name);
    }

    static std::string texturePath(const char* texPath)
    {
        if(texPath == nullptr) return std::string();
        if(texPath[0] == '/') return texPath;
        std::string res = MODULES_DIRECTORY;
        res += texPath;
        return res;
    }

    void importPlugins(mvc::Vector<Plugin>& plugins)
    {
        plugins.clear();
        booba::APPCONTEXT = reinterpret_cast<booba::ApplicationContext* >(&GEditor::app->context);
        mInfo << "isDir " << std::filesystem::is_directory(MODULES_DIRECTORY) << mlg::endl;
        mInfo << "exists " << std::filesystem::exists(MODULES_DIRECTORY) << mlg::endl;
        for(const auto& file : std::filesystem::directory_iterator(MODULES_DIRECTORY))
        {
            mInfo << "File found: " << file.path().c_str() << mlg::endl;
            std::string path = file.path();
            if(path.ends_with(".aboba.so")) {
                mInfo << "It's an module! " << mlg::endl;
                void* library = dlopen(path.c_str(), RTLD_NOW);
                if(!library) mInfo << "Error: " << dlerror() << mlg::endl;
                mAssert(library);
                GUID (*getGUIDF)(void) = reinterpret_cast<GUID (*)()>(dlsym(library, "getGUID"));

                if(!getGUIDF)
                {
                    mError << "Plugin \"" << file.path().filename().c_str() << "\" has no getGUID(). Probably it's using v1.0.0 standart. It's not supported." << mlg::endl;
                    continue;
                }
                GUID guid = (*getGUIDF)();
                if(guid.str[36] != 0)
                {
                    mError << "Plugin \"" << file.path().filename().c_str() << "\" has bad GUID" << mlg::endl;
                    continue;
                }
                plugins.push_back({guid, library});
            }
        }
        mInfo << "Plugin loading finished " << mlg::Logger::CoStyle::Green << "successfully" << mlg::Logger::CoStyle::Reset <<". Starting initialization." << mlg::endl;
        for(Plugin& plugin : plugins)
        {
            void (*startF)(void) = reinterpret_cast<void (*)()>(dlsym(plugin.handler, "init_module"));
            if(!startF)
            {
                mError << "Plugin [" << plugin.guid.str << "] has no init function." << mlg::endl;
                continue;
            }
            mInfo << "StartF address: " << reinterpret_cast<void*>(startF) << mlg::endl;
            (*startF)();
        }
        mInfo << "Plugin initialization finished " << mlg::Logger::CoStyle::Green << "successfully." << mlg::endl;
        }

    PluginTool::PluginTool(booba::Tool* tool) : tool_(tool), texName_(texturePath(tool->getTexture())) {}


    void PluginTool::onMousePress  (const ToolAction& action)
    {
        ToolGuard tg(this);
        PluginImage img(action.image);
        ev.Oleg.mbedata.ctrl  = action.ctrl;
        ev.Oleg.mbedata.shift = action.shift;
        ev.Oleg.mbedata.alt   = action.alt;
        ev.Oleg.mbedata.button = booba::MouseButton::Left;
        ev.Oleg.mbedata.x = action.point.x;
        ev.Oleg.mbedata.y = action.point.y;
        ev.type = booba::EventType::MousePressed;
        tool_->apply(&img, &ev);
    }

    void PluginTool::onMouseRelease(const ToolAction& action)
    {
        ToolGuard tg(this);
        PluginImage img(action.image);
        ev.Oleg.mbedata.ctrl  = action.ctrl;
        ev.Oleg.mbedata.shift = action.shift;
        ev.Oleg.mbedata.alt   = action.alt;
        ev.Oleg.mbedata.button = booba::MouseButton::Left;
        ev.Oleg.mbedata.x = action.point.x;
        ev.Oleg.mbedata.y = action.point.y;
        ev.type = booba::EventType::MouseReleased;

        tool_->apply(&img, &ev);
    }
    
    void PluginTool::onButtonClick(const PluginButton* button)
    {
        ToolGuard tg(this);
        ev.type = booba::EventType::ButtonClicked;
        ev.Oleg.bcedata.id = reinterpret_cast<uint64_t>(button);
        tool_->apply(nullptr, &ev); // FIXME: current image.
    }

    void PluginTool::onScrollMove(int32_t value, const PluginScroll* scroll)
    {
        ToolGuard tg(this);
        ev.type = booba::EventType::SliderMoved;
        ev.Oleg.smedata.id    = reinterpret_cast<uint64_t>(scroll);
        ev.Oleg.smedata.value = value;
        tool_->apply(nullptr, &ev); // FIXME: current image.
    }


    void PluginTool::onMouseMove   (const ToolAction& action)
    {
        ToolGuard tg(this);
        PluginImage img(action.image);
        ev.Oleg.motion.rel_x = action.point.x - prevMove_.x;
        ev.Oleg.motion.rel_y = action.point.y - prevMove_.y;
        prevMove_ = action.point;
        ev.Oleg.motion.x = action.point.x;
        ev.Oleg.motion.y = action.point.y;
        ev.type = booba::EventType::MouseMoved;
        currentPlugin = this;
        tool_->apply(&img, &ev);
        currentPlugin = nullptr;
    }

    PluginTool* PluginTool::currentPlugin = nullptr;

    aGL::EventHandlerState PluginButton::onPaintEvent(const aGL::Event* event)
    {
        if(!needsRepaint_) return aGL::Accepted;
        
        aGL::Color drawColor = Design::ColorPalete::borderLightColor;
        if(hovered_) drawColor = Design::ColorPalete::borderDarkColor;
        if(pressed_) drawColor = Design::ColorPalete::backgroundColor;

        surface->drawRect({0, 0, rect_.w, rect_.h}, drawColor);
        surface->drawText(text_);
        needsRepaint_ = false;
        return aGL::Accepted;
    }

    void PluginTool::createPanel()
    {
        ToolGuard tg(this);
        // Tool::createPanel(parent, rect);
        tool_->buildSetupWidget();
        if(!panel_) createDefaultPanel();
    }

    void PluginTool::createDefaultPanel()
    {
        mAssert(!panel_);
        panel_ = new aGL::ContainerWidget(aGL::Rect(0, 0, 1000, 1000));
    }


    bool PluginTool::setToolbarSize(size_t w, size_t h)
    {
        if(panel_) return false;
        if(w > 3000 || h > 3000) return false;
        panel_ = new aGL::ContainerWidget(aGL::Rect(0, 0, w, h));
        return panel_;
    }


    aGL::EventHandlerState PluginCanvas::onMouseButtonPressEvent(const aGL::Event* event)
    {
        aGL::Widget::onMouseButtonPressEvent(event);
        if(event->mbed.button != aGL::MouseButton::Left) return aGL::Dropped;
        booba::Event ev;
        ev.type = booba::EventType::CanvasMPressed;
        ev.Oleg.cedata.id = reinterpret_cast<uint64_t>(this);
        ev.Oleg.cedata.x = event->mbed.point.x;
        ev.Oleg.cedata.y = event->mbed.point.y;
        mousePressed.emit(ev);
        return aGL::Accepted;
    }

    aGL::EventHandlerState PluginCanvas::onMouseButtonReleaseEvent(const aGL::Event* event)
    {
        aGL::Widget::onMouseButtonReleaseEvent(event);
        if(event->mbed.button != aGL::MouseButton::Left) return aGL::Dropped;
        booba::Event ev;
        ev.type = booba::EventType::CanvasMReleased;
        ev.Oleg.cedata.id = reinterpret_cast<uint64_t>(this);
        ev.Oleg.cedata.x = event->mbed.point.x;
        ev.Oleg.cedata.y = event->mbed.point.y;
        mouseReleased.emit(ev);
        return aGL::Accepted;
    }

    aGL::EventHandlerState PluginCanvas::onMouseMoveEvent(const aGL::Event* event)
    {
        aGL::Widget::onMouseButtonPressEvent(event);
        booba::Event ev;
        ev.type = booba::EventType::CanvasMMoved;
        ev.Oleg.cedata.id = reinterpret_cast<uint64_t>(this);
        ev.Oleg.cedata.x = event->mmed.point.x;
        ev.Oleg.cedata.y = event->mmed.point.y;
        mouseMoved.emit(ev);
        return aGL::Accepted;
    }


    void PluginCanvas::setPixel (size_t x, size_t y, aGL::Color color)
    {
        assert(x < surface->getSurfRect().w);
        assert(y < surface->getSurfRect().h);
        assert(x >= 0);
        assert(y >= 0);
        surface->drawPoint(aGL::Point(x, y), color);
    }

    void PluginCanvas::clear(aGL::Color color)
    {
        surface->clear(color);
    }

    void PluginCanvas::putSprite(size_t x, size_t y, size_t w, size_t h, const char* texture)
    {

        aGL::Texture tex(texturePath(texture).c_str());
        mInfo << "Module asked for: " << texturePath(texture).c_str() << mlg::endl;
        if(!std::filesystem::exists(texturePath(texture).c_str()))
        {
            mError << "File: " << texturePath(texture).c_str() << mlg::Logger::CoStyle::Red << " not exists" << mlg::endl;
        }
        tex.setRepeated(true);
        surface->drawSprite(aGL::Point(x, y), aGL::Sprite(tex, aGL::Rect(0, 0, w, h)));
    }

    void PluginTool::onCanvasEvent(const booba::Event ev)
    {
        ToolGuard tg(this);
        tool_->apply(nullptr, &ev);
    }


}
 
namespace booba {

    static bool operator==(const GUID& lhs, const GUID& rhs)
    {
        return !strncmp(lhs.str, rhs.str, sizeof(GUID));
    }

    extern "C" uint64_t createButton   (size_t x, size_t y, size_t w, size_t h, const char* name)
    {
        if(mge::PluginTool::currentPlugin == nullptr) return 0;
        if(!mge::PluginTool::currentPlugin->getPanel()) mge::PluginTool::currentPlugin->createDefaultPanel();
        const uint32_t offs = mge::Design::LeftPanel::ToolPanel::HEAD.h;
        auto button =  new mge::PluginButton(aGL::Rect(x, y + offs, w, h), name, mge::PluginTool::currentPlugin->getPanel());
        aGL::connect(button, &mge::PluginButton::clicked, mge::PluginTool::currentPlugin, &mge::PluginTool::onButtonClick);
        return reinterpret_cast<uint64_t>(button);
    }

    extern "C" uint64_t createLabel(size_t x, size_t y, size_t w, size_t h, const char* name)
    {
        if(mge::PluginTool::currentPlugin == nullptr) return 0;
        if(!mge::PluginTool::currentPlugin->getPanel()) mge::PluginTool::currentPlugin->createDefaultPanel();
        const uint32_t offs = mge::Design::LeftPanel::ToolPanel::HEAD.h;
        auto label =  new aGL::Label(name, x, y + offs, w, h, mge::PluginTool::currentPlugin->getPanel());
        if(GEditor::app->sm_)
        {
            label->setFont(GEditor::app->sm_->getFont());
        }
        label->setTextColor(mge::Design::ColorPalete::TextColor);
        label->setTextSize(3 * h / 4);
        label->text_.setStyle(aGL::Text::Bold);
        return reinterpret_cast<uint64_t>(label);
    }

    extern "C" uint64_t createSlider(size_t x, size_t y, size_t w, size_t h, int64_t minValue, int64_t maxValue, int64_t startValue)
    {
        if(mge::PluginTool::currentPlugin == nullptr) return 0;
        if(!mge::PluginTool::currentPlugin->getPanel()) mge::PluginTool::currentPlugin->createDefaultPanel();
        const uint32_t offs = mge::Design::LeftPanel::ToolPanel::HEAD.h;
        auto scrollbar =  new mge::PluginScroll(aGL::Rect(x, y + offs, w, h), mge::PluginTool::currentPlugin->getPanel());
        scrollbar->setMinValue(minValue);
        scrollbar->setMaxValue(maxValue);
        scrollbar->setValue(startValue);
        aGL::connect(scrollbar, &mge::PluginScroll::valueChangedPtr, mge::PluginTool::currentPlugin, &mge::PluginTool::onScrollMove);

        return reinterpret_cast<uint64_t>(scrollbar);
    }
    
    extern "C" uint64_t createCanvas(size_t x, size_t y, size_t w, size_t h)
    {
        if(mge::PluginTool::currentPlugin == nullptr) return 0;
        if(!mge::PluginTool::currentPlugin->getPanel()) mge::PluginTool::currentPlugin->createDefaultPanel();
        const uint32_t offs = mge::Design::LeftPanel::ToolPanel::HEAD.h;
        auto canvas =  new mge::PluginCanvas(aGL::Rect(x, y + offs, w, h), mge::PluginTool::currentPlugin->getPanel());
        aGL::connect(canvas, &mge::PluginCanvas::mouseMoved, mge::PluginTool::currentPlugin, &mge::PluginTool::onCanvasEvent);
        aGL::connect(canvas, &mge::PluginCanvas::mousePressed, mge::PluginTool::currentPlugin, &mge::PluginTool::onCanvasEvent);
        aGL::connect(canvas, &mge::PluginCanvas::mouseReleased, mge::PluginTool::currentPlugin, &mge::PluginTool::onCanvasEvent);
        mInfo << "Canvas requested\n";
        return reinterpret_cast<uint64_t>(canvas);
    }

    extern "C" void setPixel (uint64_t canvasId, size_t x, size_t y, uint32_t color)
    {
        // mWarning << "Pix putting" << '\n';
        if(canvasId == 0) return;

        mge::PluginCanvas* canvas = reinterpret_cast<mge::PluginCanvas* >(canvasId); //FIXME: very unsafe.
        canvas->setPixel(x, y, color);  
    }

    extern "C" void cleanCanvas (uint64_t canvasId, uint32_t color)
    {
        if(canvasId == 0) return;

        mge::PluginCanvas* canvas = reinterpret_cast<mge::PluginCanvas* >(canvasId); //FIXME: very unsafe.
        canvas->clear(color);
    }

    extern "C" void putSprite(uint64_t canvasId, size_t x, size_t y, size_t w, size_t h, const char* texture)
    {
        if(canvasId == 0) return;
        mge::PluginCanvas* canvas = reinterpret_cast<mge::PluginCanvas* >(canvasId); //FIXME: very unsafe.
        canvas->putSprite(x, y, w, h, texture);
    }
    
    extern "C" void addTool(Tool* tool)
    {
        mInfo << "Plugin called add tool\n";
        GEditor::app->addTool(new mge::PluginTool(tool));
    }

    extern "C" void addFilter(Tool* tool)
    {
        MLG_UIMPLEMENTED
        addTool(tool);
    }

    extern "C" void* getLibSymbol(GUID guid, const char* name)
    {
        mInfo << "Requested lib symbol from [" << guid.str << "] with name \"" << name << "\"" << mlg::endl;
        for(const mge::Plugin& plugin : GEditor::app->plugins_)
        {
            if(guid == plugin.guid)
            {
                void* sym = dlsym(plugin.handler, name);
                return sym;
            }
        }
        return nullptr;
    }

    extern "C" bool setToolBarSize(size_t w, size_t h)
    {
        if(mge::PluginTool::currentPlugin == nullptr) return 0;
        return mge::PluginTool::currentPlugin->setToolbarSize(w, h);
    }

}

