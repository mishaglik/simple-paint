#include "Application.hpp"
#include "AbstractGL/AWindow.hpp"
#include "Raytracer/RenderPlane.hpp"
#include "Raytracer/RenderSphere.hpp"
#include <chrono>
#include <iostream>

Application::Application() : 
    logger(std::cerr)
{
    logger.setLogLevel(mlg::Logger::LogLevel::INFO);
    setGlobalLogger(&logger);

    sm_.loadSkinset("/home/gms/progs++/vecplot/skins/minimalistic");

    scene_ = new Scene();
    fillScene();

    window_ = new MainWindow(scene_);
    window_->setEventManager(&eventManager_);
    aGL::connect<aGL::WWindow>(window_, &aGL::WWindow::quited, this, &Application::quit);

    window_->setSkinManager(&sm_);
    aGL::connect(window_, &MainWindow::abobed, this, &Application::owlOnGlobe);

    state_ = AppState::Ready;
}


void Application::fillScene()
{
    scene_->addObject(new RTObjs::RenderPlane ({   0,      1, 0.05}, {0, 150,0}));
    globusImage_.loadFromFile("/home/gms/progs++/vecplot/Globus.jpg");

    RTObjs::Material material = RTObjs::MaterialCollection::Mirror;
    RTObjs::Material materialTextured;
    materialTextured.color = aGL::Colors::White;
    materialTextured.diffCoef = 0.9;
    materialTextured.reflCoef = 0.05;
    materialTextured.tex = &globusImage_;
    mAssert(materialTextured.tex != nullptr);

    material.color = RTObjs::Colors::Magenta;
    
    scene_->addObject(new RTObjs::RenderSphere({   0,     20, 1000}, 100, material));
    scene_->addObject(new RTObjs::RenderSphere({ 300,    -20, 1000}, 100, materialTextured));
    scene_->addObject(new RTObjs::RenderSphere({   0,   -1e5, 1000}, 5e4, RTObjs::MaterialCollection::Sun));

    RTObjs::Material yellowSun = RTObjs::MaterialCollection::Sun;
    yellowSun.color = yellowSun.srcColor = RTObjs::Colors::Yellow;

    scene_->addObject(new RTObjs::RenderSphere({ 155,   -300, 1000},  40, yellowSun));
    
    material.color = 0xba4545ff;
    material.reflCoef = 0.1;
    material.diffCoef = 0.9;

    scene_->addObject(new RTObjs::RenderSphere({ -300,     0, 2000},  80, material));
    scene_->addObject(new RTObjs::RenderSphere({ -250,   -80,  900},  20));
    scene_->addObject(new RTObjs::RenderSphere({ -200,   -35,  600}, 150, RTObjs::MaterialCollection::Glass));
    
    // raytracer_->addObject(new RTObjs::RenderSphere({ 100,      0,  600}, 50, RTObjs::MaterialCollection::Sun));

}

Application::~Application()
{
    state_ = AppState::Died;
    delete window_;
    delete scene_;
}

int Application::exec()
{
    if(state_ != AppState::Ready)
    {
        state_ = AppState::Error;
        return -1;
    }
    state_ = AppState::Running;

    std::chrono::high_resolution_clock clock;
    auto fpsCounterTimepoint = clock.now();

    std::chrono::duration<double, std::milli> cap(1000. / 61);

    uint8_t i = 0;

    
    while (state_ == AppState::Running)
    {
        auto fpsCapTimepoint = clock.now();

        aGL::Event event;


        event.type = aGL::EventType::Paint;
        eventManager_.handleEvent(&event);

        window_->render();

        event.type = aGL::EventType::TimerTicked;
        event.time = clock.now();

        eventManager_.handleEvent(&event);


        std::this_thread::sleep_until(fpsCapTimepoint + cap);
        
        if(!++i){
            auto nowTimepoint = clock.now();            
            std::chrono::duration<double, std::milli> delta = nowTimepoint - fpsCounterTimepoint;
            mWarning << "FPS: " << 256000 / (std::chrono::duration_cast<std::chrono::milliseconds>(delta)).count() << mlg::endl;
            fpsCounterTimepoint = nowTimepoint;
        }
    }
    
    state_ = AppState::Stopped;
    return 0;
}

aGL::EventHandlerState Application::handleEvent(const aGL::Event* event)
{
    if(event->type == aGL::EventType::Quited){
        state_ = AppState::Stopping;
        return aGL::EventHandlerState::Accepted;
    }

    if(event->type == aGL::EventType::KeyPressed)
    {
        if(event->ked.key == aGL::KeyboardKey::Num0)
            logger.setLogLevel(mlg::Logger::LogLevel::DEBUG);
        else if(event->ked.key == aGL::KeyboardKey::Num1)
            logger.setLogLevel(mlg::Logger::LogLevel::INFO);
        else if(event->ked.key == aGL::KeyboardKey::Num2)
            logger.setLogLevel(mlg::Logger::LogLevel::WARNING);
        else if(event->ked.key == aGL::KeyboardKey::Num3)
            logger.setLogLevel(mlg::Logger::LogLevel::ERROR);
        else if(event->ked.key == aGL::KeyboardKey::Num4)
            logger.setLogLevel(mlg::Logger::LogLevel::FATAL);
        return aGL::EventHandlerState::Accepted;
    }

    return aGL::EventHandlerState::Dropped;
}


void Application::quit (){
    state_ = AppState::Stopping;
}



void Application::owlOnGlobe()
{
    globusImage_ = aGL::Image("/home/gms/progs++/vecplot/owl.png");
}
