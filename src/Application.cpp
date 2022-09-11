#include "Application.hpp"
#include "AbstractGL/AWindow.hpp"
#include "VectorPlot.hpp"
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>

Application::Application(){
    window_ = new aGL::Window(800, 600, "Vecplot window");
    plotRotator_ = new VectorPlot(10, 20, 300, 300, -10, 10, 10, -10);
    plotRotator_->setVector({10, 10});
    
    state_ = AppState::Ready;
}

Application::~Application(){
    state_ = AppState::Died;
}

int Application::exec(){
    if(state_ != AppState::Ready){
        state_ = AppState::Error;
        return -1;
    }
    state_ = AppState::Running;

    while (state_ == AppState::Running) {
        aGL::Event event;
        while(window_->pollEvent(event)){
            handleEvent(event);
        }
        window_->clear(0x999999FF);
        plotRotator_->render(*window_); //TODO: change signature to window* 
        // plotClicked_->render(*window_);
        window_->update();
        
        sf::sleep(sf::milliseconds(10));
        plotRotator_->setVector(mgm::rotate(plotRotator_->getVector(), 0.01));
    }
    
    state_ = AppState::Stopped;
    return 0;
}

int Application::handleEvent(const aGL::Event& event){
    if(event.type == aGL::EventType::Exit){
        state_ = AppState::Stopping;
        return 1;
    }
    return 0;
}



