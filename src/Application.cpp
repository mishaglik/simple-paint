#include "Application.hpp"
#include "AbstractGL/AWindow.hpp"
#include "Raytracer/RenderPlane.hpp"
#include "Raytracer/RenderSphere.hpp"
#include "VectorPlot.hpp"
#include <chrono>
#include <iostream>

Application::Application() : 
    logger(std::cerr)
{
    logger.setLogLevel(mlg::Logger::LogLevel::WARNING);
    setGlobalLogger(&logger);

    window_ = new aGL::Window(800, 600, "Vecplot window");
    plotRotator_ = new VectorPlot(10, 30, 300, 300, -10, 10, 10, -10);
    plotRotator_->setVector({10, 0});

    eventManager_.subscribeOn(aGL::EventType::MouseButtonPressed, plotRotator_);
    eventManager_.subscribeOn(aGL::EventType::MouseMoved, plotRotator_);
    eventManager_.subscribeOn(aGL::EventType::Paint, plotRotator_);
    
    raytracer_ = new Raytracer(300, 0 ,500, 500);
    
    fillScene();

    exitButton  = new aGL::Button("Exit", 0, 400);
    exitButton->setEventFunction(this, Slots::Quit);

    eventManager_.subscribeOn(aGL::EventType::MouseButtonPressed, exitButton);
    eventManager_.subscribeOn(aGL::EventType::Paint, exitButton);
    

    resetButton = new aGL::Button("Reset", 200, 400);
    resetButton->setEventFunction(this, Slots::Reset);

    eventManager_.subscribeOn(aGL::EventType::MouseButtonPressed, resetButton);
    eventManager_.subscribeOn(aGL::EventType::Paint, resetButton);

    state_ = AppState::Ready;
}


void Application::fillScene()
{
    raytracer_->addObject(new RTObjs::RenderPlane ({   0,      1, 0.05}, {0, 150,0}));

    RTObjs::Material material = RTObjs::MaterialCollection::Mirror;
    material.color = RTObjs::Colors::Magenta;
    
    raytracer_->addObject(new RTObjs::RenderSphere({   0,     20, 1000}, 100, material));
    raytracer_->addObject(new RTObjs::RenderSphere({ 300,    -20, 1000}, 100));
    raytracer_->addObject(new RTObjs::RenderSphere({   0,   -1e5, 1000}, 5e4, RTObjs::MaterialCollection::Sun));

    RTObjs::Material yellowSun = RTObjs::MaterialCollection::Sun;
    yellowSun.color = yellowSun.srcColor = RTObjs::Colors::Yellow;

    raytracer_->addObject(new RTObjs::RenderSphere({ 155,   -300, 1000},  40, yellowSun));
    
    material.color = 0xba4545ff;
    material.reflCoef = 0.1;
    material.diffCoef = 0.9;

    raytracer_->addObject(new RTObjs::RenderSphere({ -300,     0, 2000},  80, material));
    raytracer_->addObject(new RTObjs::RenderSphere({ -250,   -80,  900},  20));
    raytracer_->addObject(new RTObjs::RenderSphere({ -200,   -35,  600}, 150, RTObjs::MaterialCollection::Glass));
    
    // raytracer_->addObject(new RTObjs::RenderSphere({ 100,      0,  600}, 50, RTObjs::MaterialCollection::Sun));

}

Application::~Application()
{
    state_ = AppState::Died;
    delete raytracer_;
    delete plotRotator_;
    delete window_;
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
        while(window_->pollEvent(event))
        {
            eventManager_.handleEvent(&event);
        }

        window_->clear(0x999999FF);

        event.type = aGL::EventType::Paint;
        eventManager_.handleEvent(&event);

        plotRotator_->render(*window_); //TODO: change signature to window* 
        exitButton  ->render(*window_);
        resetButton ->render(*window_);        
        raytracer_  ->render(*window_);
    
        plotRotator_->update();
        window_->update();

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

void Application::reset(){
    plotRotator_->setAngle(0);
    plotRotator_->setVector({10, 0});
}

void Application::handleSignal(int s, void*){
    Slots signal = static_cast<Slots>(s);

    switch (signal) {
    case Slots::Nothing:
    break;
    
    case Slots::Quit:
        quit();
    break;

    case Slots::Reset:
        reset();
    break;
    }
}
