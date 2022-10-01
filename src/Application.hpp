#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "VectorPlot.hpp"
#include <AbstractGL/AWindow.hpp>
#include <AbstractGL/Button.hpp>
#include <AbstractGL/EventManager.hpp>
#include <Raytracer/Raytracer.hpp>

class Application : public aGL::AObject{
    aGL::Window* window_     = nullptr;
    VectorPlot* plotRotator_ = nullptr;

    Raytracer* raytracer_    = nullptr;
    
    aGL::Button* exitButton  = nullptr;
    aGL::Button* resetButton = nullptr;

    mlg::ConsoleLogger logger;

    aGL::EventManager eventManager_;

    enum class AppState{
        UnInit = 0,
        Ready,
        Running,
        Stopping,
        Stopped,
        Died,
        Error
    };

    AppState state_ = AppState::UnInit;

    enum Slots : int{
        Nothing,
        Quit,
        Reset,
    };

    void fillScene();

public:
    Application();
    Application(int , const char** ) : Application() {}
    
    ~Application() override;

    void handleSignal(int signal, void*) override;

    int exec();

    aGL::EventHandlerState handleEvent(const aGL::Event* event) override;

    void quit ();
    void reset();

    Application(const Application& app)             = delete;
    Application& operator= (const Application& app) = delete;

};

#endif /* APPLICATION_HPP */
