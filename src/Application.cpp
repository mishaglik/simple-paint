#include "Application.hpp"
#include "AbstractGL/AWindow.hpp"
#include "Raycaster.hpp"
#include "VectorPlot.hpp"
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>

Application::Application(){
    window_ = new aGL::Window(800, 600, "Vecplot window");
    plotRotator_ = new VectorPlot(10, 20, 300, 300, -10, 10, 10, -10);
    plotRotator_->setVector({10, 0});
    
    raycaster_ = new Raycaster(300, 0, 500);

    exitButton  = new aGL::Button("Exit", 0, 400);
    exitButton->setEventFunction(this, Slots::Quit);

    resetButton = new aGL::Button("Reset", 200, 400);
    resetButton->setEventFunction(this, Slots::Reset);

    state_ = AppState::Ready;
}

Application::~Application(){
    state_ = AppState::Died;
    delete raycaster_;
    delete plotRotator_;
    delete window_;
}

int Application::exec(){
    if(state_ != AppState::Ready){
        state_ = AppState::Error;
        return -1;
    }
    state_ = AppState::Running;

    sf::Clock fpsCounter;
    uint8_t i = 0;
    while (state_ == AppState::Running) {
        sf::Clock fpsTimer;

        aGL::Event event;
        while(window_->pollEvent(event)){
            handleEvent(event);
        }
        window_->clear(0x999999FF);

        plotRotator_->render(*window_); //TODO: change signature to window* 
        raycaster_  ->render(*window_);  
        exitButton  ->render(*window_);
        resetButton ->render(*window_);
        
        
        raycaster_  ->addAngle(0.03);
        plotRotator_->update();
        window_->update();

        sf::sleep(sf::milliseconds(std::max(0, 16 - fpsTimer.getElapsedTime().asMilliseconds())));
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
