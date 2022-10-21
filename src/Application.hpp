#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "VectorPlot.hpp"
#include "Widgets/Scrollbar.hpp"
#include "Widgets/SkinManager.hpp"
#include "Widgets/TextInput.hpp"
#include <AbstractGL/AWindow.hpp>
#include <Widgets/Button.hpp>
#include <AbstractGL/EventManager.hpp>
#include <Raytracer/Raytracer.hpp>
#include <Widgets/WindowWidget.hpp>
#include <Widgets/Menubar.hpp>

class Application : public aGL::AObject{
    aGL::WWindow* window_     = nullptr;
    VectorPlot* plotRotator_ = nullptr;

    Raytracer* raytracer_    = nullptr;
    
    aGL::Menubar* menubar_ = nullptr;
    aGL::Scrollbar* scrollbarX_ = nullptr;
    aGL::Scrollbar* scrollbarY_ = nullptr;

    aGL::PushButton* exitButton  = nullptr;
    aGL::PushButton* resetButton = nullptr;

    aGL::TextInput* textInput_ = nullptr;

    mlg::ConsoleLogger logger;
    Scene* scene_ = nullptr;

    aGL::EventManager eventManager_;

    aGL::SkinManager sm;

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

    bool vecPlotVisible = true;
    void toggleVecplotVisibility();

public:
    Application();
    Application(int , const char** ) : Application() {}
    
    ~Application();

    int exec();

    aGL::EventHandlerState handleEvent(const aGL::Event* event);

    void quit ();
    void reset();


    Application(const Application& app)             = delete;
    Application& operator= (const Application& app) = delete;

};

#endif /* APPLICATION_HPP */
