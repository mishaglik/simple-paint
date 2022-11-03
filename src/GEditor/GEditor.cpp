#include "GEditor.hpp"
#include <thread>

GEditor::GEditor(int, const char**)
{
    setGlobalLogger(new mlg::ConsoleLogger(std::cerr));
    getGlobalLogger().setLogLevel(mlg::Logger::LogLevel::INFO);
    mInfo << "GEditor started" << mlg::endl;

    mainWindow_ = new mge::MainWindow;
    mainWindow_->quited.connect(this, &GEditor::quit);

    sm_ = new aGL::SkinManager;
    sm_->loadSkinset("/home/gms/progs++/vecplot/skins/minimalistic"); //TODO: Better default path.
    mainWindow_->setSkinManager(sm_);

    appState_ = Ready;
}

GEditor::~GEditor()
{
    delete sm_;
    delete mainWindow_;
    delete &getGlobalLogger(); // Delete global logger.
}

int GEditor::exec()
{
    mAssert(appState_ == Ready);
    appState_ = Runnig;
    int ret = 0;
    try {
        ret = eventLoop();
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

int GEditor::eventLoop()
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

        mainWindow_->onTimerEvent(&event);
        
        event.type = aGL::EventType::Paint;
        mainWindow_->onPaintEvent(&event);
        mainWindow_->render();
        
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

void GEditor::quit()
{
    appState_ = Stopping;
}
