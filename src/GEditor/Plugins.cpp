#include "Plugins.hpp"
#include "GEditor/GEditor.hpp"
#include <filesystem>
#include <dlfcn.h>
#include <cxxabi.h>
#include <unistd.h>

booba::ApplicationContext* booba::APPCONTEXT = nullptr;

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

    void importPlugins()
    {
        booba::APPCONTEXT = reinterpret_cast<booba::ApplicationContext* >(&GEditor::app->context);
        mInfo << "isDir " << std::filesystem::is_directory("./modules") << mlg::endl;
        mInfo << "exists " << std::filesystem::exists("./modules") << mlg::endl;
        for(const auto& file : std::filesystem::directory_iterator("./modules"))
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

    void PluginTool::onMousePress  (const ToolAction& action)
    {
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
    
    void PluginTool::onMouseMove   (const ToolAction& action)
    {
        PluginImage img(action.image);
        ev.Oleg.motion.rel_x = action.point.x - prevMove_.x;
        ev.Oleg.motion.rel_y = action.point.y - prevMove_.y;
        prevMove_ = action.point;
        ev.Oleg.motion.x = action.point.x;
        ev.Oleg.motion.y = action.point.y;
        ev.type = booba::EventType::MouseMoved;
        tool_->apply(&img, &ev);
    }
}

namespace booba {
    extern "C" uint64_t createButton   (int32_t x, int32_t y, uint32_t w, uint32_t h, const char* name)
    {
        MLG_UIMPLEMENTED
        return 0;
    }

    extern "C" uint64_t createLabel    (int32_t x, int32_t y, uint32_t w, uint32_t h, const char*)
    {
        MLG_UIMPLEMENTED
        return 0;
    }
    extern "C" uint64_t createScrollbar(int32_t x, int32_t y, uint32_t w, uint32_t h)
    {
        MLG_UIMPLEMENTED
        return 0;
    }
    
    extern "C" uint64_t createCanvas(int32_t x, int32_t y, int32_t w, int32_t h)
    {
        MLG_UIMPLEMENTED
        return 0;
    }

    extern "C" uint64_t putPixel (uint64_t canvas, int32_t x, int32_t y, uint32_t color)
    {
        MLG_UIMPLEMENTED
        return 0;
    }

    extern "C" uint64_t putSprite(uint64_t canvas, int32_t x, int32_t y, uint32_t w, uint32_t h, const char* texture)
    {
        MLG_UIMPLEMENTED
        return 0;
    }
    
    extern "C" void addTool(Tool* tool)
    {
        mInfo << "Plugin called add tool\n";
        GEditor::app->addTool(new mge::PluginTool(tool));
    }

    extern "C" void addFilter(Tool* tool)
    {
        addTool(tool);
    }

    Image::~Image() {}
    Tool::~Tool() {}
}

