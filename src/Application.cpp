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
    logger.setLogLevel(mlg::Logger::LogLevel::INFO);
    setGlobalLogger(&logger);

    sm.loadSkinset("/home/gms/progs++/vecplot/skins/default");

    window_ = new aGL::WWindow(800, 600, "Vecplot window");
    window_->setEventManager(&eventManager_);
    aGL::connect(window_, &aGL::WWindow::quited, this, &Application::quit);

    plotRotator_ = new VectorPlot(10, 30, 300, 300, -10, 10, 10, -10, window_);
    plotRotator_->setVector({10, 0});

    window_->subscribe(plotRotator_);
    
    scene_ = new Scene();
    raytracer_ = new Raytracer(scene_, 300, 0 ,500, 500);
    
    fillScene();

    exitButton  = new aGL::PushButton("Exit", 5, 400, 500, 40, window_);
    aGL::connect<aGL::AbstractButton>(exitButton, &aGL::AbstractButton::clicked, this, &Application::quit);
    exitButton->setSkinManager(&sm);

    window_->subscribe(exitButton);
    

    resetButton = new aGL::PushButton("Reset", 200, 400, 50, 100, window_);
    aGL::connect<aGL::AbstractButton>(resetButton, &aGL::AbstractButton::clicked, this, &Application::reset);

    window_->subscribe(resetButton);
    
    menubar_ = new aGL::Menubar(0,0, 800, 20, window_);
    menubar_->addMenuEntry("File");
    menubar_->entries()[0]->addMenuEntry("Aboba");
    menubar_->entries()[0]->addMenuEntry("Quit");
    menubar_->entries()[0]->buttons()[1]->clicked.connect(this, &Application::quit);

    menubar_->addMenuEntry("Vecplot");
    aGL::Menubar::Menu* vecplotMenu = menubar_->entries()[1];
    vecplotMenu->addMenuEntry("Hide");
    vecplotMenu->buttons()[0]->clicked.connect(this, &Application::toggleVecplotVisibility);
    vecplotMenu->addMenuEntry("Reset");
    vecplotMenu->buttons()[1]->clicked.connect(this, &Application::reset);

    menubar_->addMenuEntry("Raytracer");
    window_->subscribe(menubar_);

    scrollbarX_ = new aGL::Scrollbar(300, 400, 400, 20, aGL::Scrollbar::Horizontal, window_);
    scrollbarX_->setMaxValue(100);
    scrollbarX_->valueChanged.connect(raytracer_, &Raytracer::setStartX);
    window_->subscribe(scrollbarX_);

    scrollbarY_ = new aGL::Scrollbar(700, 0, 20, 400, aGL::Scrollbar::Vertical, window_);
    scrollbarY_->setMaxValue(100);
    scrollbarY_->valueChanged.connect(raytracer_, &Raytracer::setStartY);
    window_->subscribe(scrollbarY_);


    textInput_ = new aGL::TextInput(10, 500, 100, 30, window_);
    window_->subscribe(textInput_);

    state_ = AppState::Ready;
}


void Application::fillScene()
{
    scene_->addObject(new RTObjs::RenderPlane ({   0,      1, 0.05}, {0, 150,0}));

    RTObjs::Material material = RTObjs::MaterialCollection::Mirror;
    material.color = RTObjs::Colors::Magenta;
    
    scene_->addObject(new RTObjs::RenderSphere({   0,     20, 1000}, 100, material));
    scene_->addObject(new RTObjs::RenderSphere({ 300,    -20, 1000}, 100));
    scene_->addObject(new RTObjs::RenderSphere({   0,   -1e5, 1000}, 5e4, RTObjs::MaterialCollection::Sun));

    RTObjs::Material yellowSun = RTObjs::MaterialCollection::Sun;
    yellowSun.color = yellowSun.srcColor = RTObjs::Colors::Yellow;

    scene_->addObject(new RTObjs::RenderSphere({ 155,   -300, 1000},  40, yellowSun));
    
    material.color = 0xba4545ff;
    material.reflCoef = 0.1;
    material.diffCoef = 0.9;

    scene_->addObject(new RTObjs::RenderSphere({ -300,     0, 2000},  80, material));
    scene_->addObject(new RTObjs::RenderSphere({ -250,   -80,  900},  20));
    scene_->addObject(new RTObjs::RenderSphere({ -200,   -35,  600}, 150, RTObjs::MaterialCollection::Glass));
    
    // raytracer_->addObject(new RTObjs::RenderSphere({ 100,      0,  600}, 50, RTObjs::MaterialCollection::Sun));

}

Application::~Application()
{
    state_ = AppState::Died;
    delete raytracer_;
    delete scene_;
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
        // while(window_->pollEvent(event))
        // {
        //     eventManager_.handleEvent(&event);
        // }

        window_->clear(0x999999FF);

        event.type = aGL::EventType::Paint;
        eventManager_.handleEvent(&event);

        // plotRotator_->render(*window_); //TODO: change signature to window* 
        // exitButton  ->render(*window_);
        // resetButton ->render(*window_);        
        raytracer_  ->render(*window_);
        // menubar_    ->render(*window_);
        // scrollbarX_ ->render(*window_);
        // scrollbarY_ ->render(*window_);
        // textInput_  ->render(*window_);
        window_->render();

        event.type = aGL::EventType::TimerTicked;
        event.time = clock.now();

        eventManager_.handleEvent(&event);

        // plotRotator_->update();
        // window_->update();

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

void Application::toggleVecplotVisibility()
{
    if(vecPlotVisible)
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

    vecPlotVisible = !vecPlotVisible;
}
