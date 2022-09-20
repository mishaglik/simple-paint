#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Raycaster.hpp"
#include "VectorPlot.hpp"
#include <AbstractGL/AWindow.hpp>
#include <AbstractGL/Button.hpp>
#include <Raytracer/Raytracer.hpp>

class Application : public AObject{
    aGL::Window* window_     = nullptr;
    VectorPlot* plotRotator_ = nullptr;
    // VectorPlot* plotClicked_ = nullptr;
    Raycaster* raycaster_    = nullptr;
    Raytracer* raytracer_    = nullptr;
    
    aGL::Button* exitButton  = nullptr;
    aGL::Button* resetButton = nullptr;

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

public:
    Application();
    Application(int , const char** ) : Application() {}
    
    ~Application() override;

    void handleSignal(int signal, void*) override;

    int exec();

    int handleEvent(const aGL::Event& event);

    void quit ();
    void reset();

    Application(const Application& app)             = delete;
    Application& operator= (const Application& app) = delete;

};

#endif /* APPLICATION_HPP */
