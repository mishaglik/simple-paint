#include "Application.hpp"
#include <thread>

namespace aGL {

BaseApplication* BaseApplication::APP = nullptr;

    BaseApplication::BaseApplication(int, const char**)
    {
        if(APP != nullptr)
        {
            mFatal << "There can be only one lord" << mlg::endl;
            throw "Two singletons";
        }
        APP = this;

        setGlobalLogger(new mlg::ConsoleLogger(std::cerr));
        getGlobalLogger().setLogLevel(mlg::Logger::LogLevel::INFO);
        mInfo << "Application started" << mlg::endl;
        
    }

    BaseApplication::~BaseApplication()
    {
        for(WWindow* w : toDelete_)
        {
            delete w;
        }

        while (!windows_.empty())
        {
            delete windows_.back();
            windows_.pop_back();
        }
        
        delete &getGlobalLogger(); // Delete global logger.
    }

    int BaseApplication::exec()
    {
        mAssert(appState_ == Ready);
        appState_ = Runnig;
        int ret = 0;
        try {
            ret = eventLoop();
        }
        catch(char* s) {
            mFatal << "Caught an exception: " << s << ". Terminating" << mlg::endl;
            appState_ = ERROR;
            return -1;
        }
        catch(...) {
            mFatal << "Caught an exception. Terminating" << mlg::endl;
            appState_ = ERROR;
            return -1;
        }
        appState_ = Died;
        mInfo << "Normal finishing GEditor with code: " << (ret ? mlg::ConsoleLogger::CoStyle::Red : mlg::ConsoleLogger::CoStyle::Green) << ret << mlg::endl;
        return ret;
    }

    int BaseApplication::eventLoop()
    {
        aGL::Event event;
        event.type = aGL::EventType::TimerTicked;
        
        std::chrono::high_resolution_clock clock;
        auto fpsCounterTimepoint = clock.now();
        
        const std::chrono::duration<double, std::milli> fpsCap(1000. / 61);
        uint8_t frameCnt = 0;
        
        while (appState_ == Runnig)
        {
            auto fpsCapTimepoint = clock.now();
            
            event.type = aGL::EventType::TimerTicked;
            event.time = clock.now();

            for(WWindow* w : windows_)
            {
                if(w) w->onTimerEvent(&event);
            }
            
            event.type = aGL::EventType::Paint;

            for(WWindow* w : windows_)
            {
                if(w)
                {
                    w->onTimerEvent(&event);
                    w->render();
                }
            }
            
            for(WWindow* w : toDelete_)
            {
                delete w;
            }
            toDelete_.resize(0);

            std::this_thread::sleep_until(fpsCapTimepoint + fpsCap);
            if(!++frameCnt){
                auto nowTimepoint = clock.now();            
                std::chrono::duration<double, std::milli> delta = nowTimepoint - fpsCounterTimepoint;
                mInfo << "FPS: " << 256000 / (std::chrono::duration_cast<std::chrono::milliseconds>(delta)).count() << mlg::endl;
                fpsCounterTimepoint = nowTimepoint;
            }
        }
        return 0;
    }

    void BaseApplication::quit()
    {
        appState_ = Stopping;
    }

    void BaseApplication::onCloseWindow(WWindow* w)
    {
        for(size_t i = 0; i < windows_.size(); ++i)
        {
            if(windows_[i] == w)
            {
                toDelete_.push_back(w);
                windows_[i] = nullptr;
                break;
            }
        }
    }

}