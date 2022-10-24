#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "AbstractGL/AImage.hpp"
#include "MainWindow.hpp"
#include "Widgets/SkinManager.hpp"
#include <AbstractGL/EventManager.hpp>
#include <Raytracer/Raytracer.hpp>
#include <Widgets/WindowWidget.hpp>
#include <Widgets/Menubar.hpp>

class Application : public aGL::AObject{
    MainWindow* window_     = nullptr;

    mlg::ConsoleLogger logger;
    Scene* scene_ = nullptr;

    aGL::EventManager eventManager_;
    aGL::Image globusImage_;
    aGL::SkinManager sm_;

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

    void fillScene();

public:
    Application();
    Application(int , const char** ) : Application() {}
    
    ~Application();

    int exec();

    aGL::EventHandlerState handleEvent(const aGL::Event* event);

    void quit ();
    void reset();
    
    void owlOnGlobe();

    Application(const Application& app)             = delete;
    Application& operator= (const Application& app) = delete;

};

#endif /* APPLICATION_HPP */
