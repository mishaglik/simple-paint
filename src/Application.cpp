#include "Application.hpp"
#include "AbstractGL/AWindow.hpp"
#include "Raycaster.hpp"
#include "Raytracer/RenderPlane.hpp"
#include "Raytracer/RenderSphere.hpp"
#include "VectorPlot.hpp"
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>

Application::Application() : 
    logger(std::cerr)
{
    logger.setLogLevel(mlg::Logger::LogLevel::INFO);
    setGlobalLogger(&logger);

    window_ = new aGL::Window(800, 600, "Vecplot window");
    plotRotator_ = new VectorPlot(10, 30, 300, 300, -10, 10, 10, -10);
    plotRotator_->setVector({10, 0});
    
    raycaster_ = new Raycaster(0, 0, 500);

    raytracer_ = new Raytracer(300, 0 ,500, 500);
    raytracer_->wind = window_;
    
    fillScene();

    exitButton  = new aGL::Button("Exit", 0, 400);
    exitButton->setEventFunction(this, Slots::Quit);

    resetButton = new aGL::Button("Reset", 200, 400);
    resetButton->setEventFunction(this, Slots::Reset);

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
}

Application::~Application()
{
    state_ = AppState::Died;
    delete raycaster_;
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

    sf::Clock fpsCounter; //FIXME
    uint8_t i = 0;

    
    while (state_ == AppState::Running)
    {
        sf::Clock fpsTimer; //FIXME

        aGL::Event event;
        while(window_->pollEvent(event))
        {
            handleEvent(event);
        }

        window_->clear(0x999999FF);
        plotRotator_->onPaintEvent();
        // raycaster_  ->onPaintEvent();
        exitButton  ->onPaintEvent();
        resetButton ->onPaintEvent();

        plotRotator_->render(*window_); //TODO: change signature to window* 
        // raycaster_  ->render(*window_);  
        exitButton  ->render(*window_);
        resetButton ->render(*window_);
        
        raytracer_  ->onPaintEvent();
        raytracer_  ->render(*window_);
        
        
        raycaster_  ->addAngle(1. / 60);
        plotRotator_->update();
        window_->update();

        sf::sleep(sf::milliseconds(std::max(0, 16 - fpsTimer.getElapsedTime().asMilliseconds()))); //FIXME: sf
        if(!++i){
            std::cerr << "FPS: " << 256000. / fpsCounter.getElapsedTime().asMilliseconds() << '\n';
            fpsCounter.restart();
        }
    }
    
    state_ = AppState::Stopped;
    return 0;
}

int Application::handleEvent(const aGL::Event& event){
    if(event.type == aGL::EventType::Quit){
        state_ = AppState::Stopping;
        return 1;
    }

    resetButton ->handleEvent(event);
    exitButton  ->handleEvent(event);
    plotRotator_->handleEvent(event);
    raycaster_  ->handleEvent(event);

    if(event.type == aGL::EventType::KeyPressedEvent)
    {
        if(event.ked.key == aGL::KeyboardKey::Num0)
            logger.setLogLevel(mlg::Logger::LogLevel::DEBUG);
        else if(event.ked.key == aGL::KeyboardKey::Num1)
            logger.setLogLevel(mlg::Logger::LogLevel::INFO);
        else if(event.ked.key == aGL::KeyboardKey::Num2)
            logger.setLogLevel(mlg::Logger::LogLevel::WARNING);
        else if(event.ked.key == aGL::KeyboardKey::Num3)
            logger.setLogLevel(mlg::Logger::LogLevel::ERROR);
        else if(event.ked.key == aGL::KeyboardKey::Num4)
            logger.setLogLevel(mlg::Logger::LogLevel::FATAL);
    }

    return 0;
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
