#include "MainWindow.hpp"

MainWindow::MainWindow(Scene* scene) :
    aGL::WWindow(1000, 600, "I've fucked up with design")
{

    raytracer_ = new Raytracer(scene, 180, 30, 620, 460, this); //TODO: Main widget
    
    scrollbarX_ = new aGL::Scrollbar(180, 490, 620, 20, aGL::Scrollbar::Horizontal, this);
    scrollbarX_->setMaxValue(100);
    scrollbarX_->valueChanged.connect(raytracer_, &Raytracer::setStartX);

    scrollbarY_ = new aGL::Scrollbar(800, 30, 20, 460, aGL::Scrollbar::Vertical, this);
    scrollbarY_->setMaxValue(100);
    scrollbarY_->valueChanged.connect(raytracer_, &Raytracer::setStartY);

    plotRotator_ = new VectorPlot(180, 30, 620, 460, -10, 10, 10, -10, this);
    plotRotator_->setVector({10, 0});
    
    exitButton  = new aGL::PushButton("Exit", 5, 400, 500, 40, this);
    aGL::connect<aGL::AbstractButton, aGL::WWindow>(exitButton, &aGL::AbstractButton::clicked, this, &aGL::WWindow::quit);
    

    // resetButton = new aGL::PushButton("Reset", 200, 400, 50, 100, this);
    // aGL::connect<aGL::AbstractButton>(resetButton, &aGL::AbstractButton::clicked, plotRotator_, &VectorPlot::reset);
    // resetButton->setTexId(aGL::IgnoreTexture);
    


    // textInput_ = new aGL::TextInput(10, 500, 100, 30, this);

    sceneEditor_ = new SceneEditor(scene, 820, 30, 180, 460, this);

    menubar_ = new aGL::Menubar(0,0, 1000, 30, this);
    setupMenu();
    toggleVecplotVisibility();
}


MainWindow::~MainWindow()
{}

void MainWindow::setupMenu()
{
    menubar_->addMenuEntry("File");
    menubar_->entries()[0]->addMenuEntry("Aboba");
    menubar_->entries()[0]->addMenuEntry("Quit");
    menubar_->entries()[0]->buttons()[1]->clicked.connect<MainWindow>(this, &MainWindow::quit);

    menubar_->addMenuEntry("Vecplot");
    aGL::Menubar::Menu* vecplotMenu = menubar_->entries()[1];
    vecplotMenu->addMenuEntry("Hide");
    vecplotMenu->buttons()[0]->clicked.connect(this, &MainWindow::toggleVecplotVisibility);
    vecplotMenu->addMenuEntry("Reset");
    vecplotMenu->buttons()[1]->clicked.connect(plotRotator_, &VectorPlot::reset);

    menubar_->addMenuEntry("Raytracer");
}

void MainWindow::toggleVecplotVisibility()
{
    if(!plotRotator_->isHidden())
    {
        plotRotator_->hide();
        menubar_->entries()[1]->buttons()[0]->setString("Show");
        menubar_->entries()[1]->buttons()[1]->hide();
    }
    else {
        plotRotator_->show();
        menubar_->entries()[1]->buttons()[0]->setString("Hide");
        menubar_->entries()[1]->buttons()[1]->show();
    }
}
