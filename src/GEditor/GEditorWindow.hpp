#ifndef GEDITOR_GEDITORWINDOW_HPP
#define GEDITOR_GEDITORWINDOW_HPP

#include "GEditor/Canvas.hpp"
#include "GEditor/LeftPanel.hpp"
#include "Widgets/WindowWidget.hpp"
#include "GEditor/CentralWidget.hpp"
#include "Layers.hpp"


namespace mge {

    class MainWindow : public aGL::WWindow
    {
        aGL::Menubar* menubar_ = nullptr;

        CentralWidget* centralWidget_ = nullptr;        

        LeftPanel* leftPanel_ = nullptr;
        // Tool* selectedTool_ = nullptr;

        LayerManager* layers_ = nullptr;

        void setupMenu();

    public:
        MainWindow();
        ~MainWindow() override;

        void onSkinChange() override;
        // void selectTool(Tool* tool);
        // aGL::Signal<Tool* > selectedToolChanged;
    private:
        void colorSelect();
        void setForegroundColor(aGL::Color color);
    };
}

#endif /* GEDITOR_GEDITORWINDOW_HPP */
