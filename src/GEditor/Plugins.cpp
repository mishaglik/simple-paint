#include "Plugins.hpp"
#include "GEditor/GEditor.hpp"
#include "Widgets/Label.hpp"
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

    void importPlugins()
    {
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
                void (*startF)(void) = reinterpret_cast<void (*)()>(dlsym(library, "init_module"));
                mAssert(startF);
                mInfo << "StartF address: " << reinterpret_cast<void*>(startF) << mlg::endl;
                (*startF)();
            }
        }
        std::cerr.flush();
        sleep(1);
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
        ev.type = booba::EventType::ScrollbarMoved;
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

    void PluginTool::createPanel(aGL::Widget *parent, const aGL::Rect &rect)
    {
        ToolGuard tg(this);
        Tool::createPanel(parent, rect);
        tool_->buildSetupWidget();
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


    void PluginCanvas::putPixel (int32_t x, int32_t y, aGL::Color color)
    {
        surface->drawPoint({x, y}, color);
    }

    void PluginCanvas::putSprite(int32_t x, int32_t y, uint32_t w, uint32_t h, const char* texture)
    {

        aGL::Texture tex(texturePath(texture).c_str());
        mInfo << "Module asked for: " << texturePath(texture).c_str() << mlg::endl;
        if(!std::filesystem::exists(texturePath(texture).c_str()))
        {
            mError << "File: " << texturePath(texture).c_str() << mlg::Logger::CoStyle::Red << " not exists" << mlg::endl;
        }
        tex.setRepeated(true);
        surface->drawSprite({x, y}, aGL::Sprite(tex, {0, 0, w, h}));
    }

}
 
namespace booba {
    extern "C" uint64_t createButton   (int32_t x, int32_t y, uint32_t w, uint32_t h, const char* name)
    {
        if(mge::PluginTool::currentPlugin == nullptr) return 0;
        const uint32_t offs = mge::Design::LeftPanel::ToolPanel::HEAD.h;
        auto button =  new mge::PluginButton(aGL::Rect(x, y + offs, w, h), name, mge::PluginTool::currentPlugin->getPanel());
        aGL::connect(button, &mge::PluginButton::clicked, mge::PluginTool::currentPlugin, &mge::PluginTool::onButtonClick);
        return reinterpret_cast<uint64_t>(button);
    }

    extern "C" uint64_t createLabel(int32_t x, int32_t y, uint32_t w, uint32_t h, const char* name)
    {
        if(mge::PluginTool::currentPlugin == nullptr) return 0;
        const uint32_t offs = mge::Design::LeftPanel::ToolPanel::HEAD.h;
        auto label =  new aGL::Label(name, x, y + offs, w, h, mge::PluginTool::currentPlugin->getPanel());
        return reinterpret_cast<uint64_t>(label);
    }

    extern "C" uint64_t createScrollbar(int32_t x, int32_t y, uint32_t w, uint32_t h, int32_t maxValue, int32_t startValue)
    {
        if(mge::PluginTool::currentPlugin == nullptr) return 0;
        const uint32_t offs = mge::Design::LeftPanel::ToolPanel::HEAD.h;
        auto scrollbar =  new mge::PluginScroll(aGL::Rect(x, y + offs, w, h), mge::PluginTool::currentPlugin->getPanel());
        scrollbar->setMaxValue(maxValue);
        scrollbar->setValue(startValue);
        aGL::connect(scrollbar, &mge::PluginScroll::valueChangedPtr, mge::PluginTool::currentPlugin, &mge::PluginTool::onScrollMove);
        return reinterpret_cast<uint64_t>(scrollbar);
    }
    
    extern "C" uint64_t createCanvas(int32_t x, int32_t y, int32_t w, int32_t h)
    {
        if(mge::PluginTool::currentPlugin == nullptr) return 0;
        const uint32_t offs = mge::Design::LeftPanel::ToolPanel::HEAD.h;
        auto canvas =  new mge::PluginCanvas(aGL::Rect(x, y + offs, w, h), mge::PluginTool::currentPlugin->getPanel());
        aGL::connect(canvas, &mge::PluginCanvas::mouseMoved, mge::PluginTool::currentPlugin, &mge::PluginTool::onCanvasEvent);
        aGL::connect(canvas, &mge::PluginCanvas::mousePressed, mge::PluginTool::currentPlugin, &mge::PluginTool::onCanvasEvent);
        aGL::connect(canvas, &mge::PluginCanvas::mouseReleased, mge::PluginTool::currentPlugin, &mge::PluginTool::onCanvasEvent);
        return reinterpret_cast<uint64_t>(canvas);
    }

    extern "C" void putPixel (uint64_t canvasId, int32_t x, int32_t y, uint32_t color)
    {
        if(canvasId == 0) return;

        mge::PluginCanvas* canvas = reinterpret_cast<mge::PluginCanvas* >(canvasId); //FIXME: very unsafe.
        canvas->putPixel(x, y, color);  
    }

    extern "C" void putSprite(uint64_t canvasId, int32_t x, int32_t y, uint32_t w, uint32_t h, const char* texture)
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

    Image::~Image() {}
    Tool::~Tool() {}
}

