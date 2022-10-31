#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "Raytracer/Raytracer.hpp"
#include "Raytracer/SceneEditor.hpp"
#include "VectorPlot.hpp"
#include "Widgets/Gui.hpp"
#include "Widgets/WindowWidget.hpp"

class MainWindow final : public aGL::WWindow
{
    VectorPlot* plotRotator_ = nullptr;

    Raytracer* raytracer_    = nullptr;
    
    aGL::Menubar* menubar_ = nullptr;
    aGL::Scrollbar* scrollbarX_ = nullptr;
    aGL::Scrollbar* scrollbarY_ = nullptr;

    aGL::PushButton* exitButton  = nullptr;

    aGL::TextInput* textInput_ = nullptr;

    SceneEditor* sceneEditor_ = nullptr;

    void setupMenu();
    void toggleVecplotVisibility();

public:
    MainWindow(Scene* scene);
    ~MainWindow() override final;

    aGL::Signal<> abobed;
    void aboba() { abobed.emit(); }
};

#endif /* MAINWINDOW_HPP */
