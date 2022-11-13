#include "GEditorWindow.hpp"
#include "BasicTools.hpp"
#include "ColorDialog/ColorDialog.hpp"
#include "GrandDesign.hpp"
#include "GEditor.hpp"

namespace mge {
    MainWindow::MainWindow() :
        aGL::WWindow(Design::Window::W, Design::Window::H, Design::Window::TITLE)
    {
        centralWidget_ = new CentralWidget(Design::MainWidget::RECT, this);
        // canvas_ = new Canvas(Design::MainWidget::RECT, this);
        // canvas_->mouseMoved   .connect(this, &MainWindow::applyToolMouseMove);
        // canvas_->mousePressed .connect(this, &MainWindow::applyToolMousePress);
        // canvas_->mouseReleased.connect(this, &MainWindow::applyToolMouseRelease);

        // imageScrollX_ = new aGL::Scrollbar(180, 490, 620, 20, aGL::Scrollbar::Horizontal, this);
        // imageScrollX_->setMaxValue(-100);
        // imageScrollX_->valueChanged.connect(canvas_, &Canvas::setImageStartX);

        // imageScrollY_ = new aGL::Scrollbar(800, 30, 20, 460, aGL::Scrollbar::Vertical, this);
        // imageScrollY_->setMaxValue(-100);
        // imageScrollY_->valueChanged.connect(canvas_, &Canvas::setImageStartY);

        leftPanel_ = new LeftPanel(Design::LeftPanel::RECT, tools_, this);

        createTools();
        // selectTool(tools_[0]);
        GEditor::app->setCurrentTool(tools_[0]);

        menubar_ = new aGL::Menubar(Design::Menu::RECT, this);
        setupMenu();
    }

    MainWindow::~MainWindow() 
    {

    }

    void MainWindow::setupMenu()
    {
        menubar_->addMenuEntry("File");
        menubar_->entries()[0]->addMenuEntry("Open file");
        menubar_->entries()[0]->addMenuEntry("Quit");
        menubar_->entries()[0]->buttons()[1]->clicked.connect<MainWindow>(this, &MainWindow::quit);
        menubar_->addMenuEntry("Edit");
        menubar_->addMenuEntry("Cringe");
        menubar_->entries()[2]->addMenuEntry("Select color");
        menubar_->entries()[2]->buttons()[0]->clicked.connect<MainWindow>(this, &MainWindow::colorSelect);
        menubar_->setTextColor(Design::Palete.TextColor);
    }



    void MainWindow::applyToolMouseMove(const ToolAction& ta)
    {
        GEditor::app->getCurrentTool()->onMouseMove(ta);
    }

    void MainWindow::applyToolMousePress(const ToolAction& ta)
    {
        GEditor::app->getCurrentTool()->onMousePress(ta);
    }

    void MainWindow::applyToolMouseRelease(const ToolAction& ta)
    {
        GEditor::app->getCurrentTool()->onMouseRelease(ta);
    }

    void MainWindow::createTools()
    {
        tools_.push_back(new tools::Pen{&context_});
        tools_.push_back(new tools::RectFiller{&context_});
        tools_.push_back(new tools::EllipseFiller{&context_});
        tools_.push_back(new tools::Filler(&context_));
        tools_.push_back(new tools::Pippet(&context_));
        tools_.push_back(new tools::Grayer(&context_));
    }

    void MainWindow::colorSelect()
    {
        aGL::ColorDialog* dialog = new aGL::ColorDialog("Fore color", context_.foregroundColor);
        dialog->Window::show();
        dialog->finished.connect(this, &MainWindow::setForegroundColor);
    }

    void MainWindow::setForegroundColor(aGL::Color color)
    {
        context_.foregroundColor = color;
    }
}
