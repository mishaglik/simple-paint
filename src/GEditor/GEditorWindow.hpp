#ifndef GEDITOR_GEDITORWINDOW_HPP
#define GEDITOR_GEDITORWINDOW_HPP

#include "GEditor/Canvas.hpp"
#include "GEditor/LeftPanel.hpp"
#include "Widgets/WindowWidget.hpp"
#include "GEditor/CentralWidget.hpp"


namespace mge {

    class MainWindow : public aGL::WWindow
    {
        aGL::Menubar* menubar_ = nullptr;

        CentralWidget* centralWidget_ = nullptr;        

        LeftPanel* leftPanel_ = nullptr;
        mvc::Vector<Tool* > tools_;
        // Tool* selectedTool_ = nullptr;
        DrawingContext context_ = {};
        void setupMenu();

    public:
        MainWindow();
        ~MainWindow() override;

        // void selectTool(Tool* tool);
        // aGL::Signal<Tool* > selectedToolChanged;
    
    private:
        void createTools();
        void colorSelect();
        void setForegroundColor(aGL::Color color);
    };
}

#endif /* GEDITOR_GEDITORWINDOW_HPP */
