#ifndef GEDITOR_GEDITORWINDOW_HPP
#define GEDITOR_GEDITORWINDOW_HPP

#include "GEditor/Canvas.hpp"
#include "GEditor/Toolbox.hpp"
#include "Widgets/Gui.hpp"
#include "Widgets/WindowWidget.hpp"

namespace mge {

    class MainWindow : public aGL::WWindow
    {
        aGL::Menubar* menubar_ = nullptr;

        aGL::Scrollbar* imageScrollX_ = nullptr;
        aGL::Scrollbar* imageScrollY_ = nullptr;

        mge::Canvas* canvas_ = nullptr;
        
        Toolbox* tb_ = nullptr;
        DrawingContext context_ = {};
        void setupMenu();

    public:
        MainWindow();
        ~MainWindow() override;
    private:
        void applyToolMouseMove(const ToolAction& ta);
        void applyToolMousePress(const ToolAction& ta);
        void applyToolMouseRelease(const ToolAction& ta);
        void createTools();
    };
}

#endif /* GEDITOR_GEDITORWINDOW_HPP */
