#include "GEditorWindow.hpp"
#include "BasicTools.hpp"
#include "ColorDialog/ColorDialog.hpp"
#include "GrandDesign.hpp"

namespace mge {
    MainWindow::MainWindow() :
        aGL::WWindow(Design::Window::W, Design::Window::H, Design::Window::TITLE)
    {
        canvas_ = new Canvas(Design::MainWidget::RECT, this);
        canvas_->mouseMoved   .connect(this, &MainWindow::applyToolMouseMove);
        canvas_->mousePressed .connect(this, &MainWindow::applyToolMousePress);
        canvas_->mouseReleased.connect(this, &MainWindow::applyToolMouseRelease);

        imageScrollX_ = new aGL::Scrollbar(180, 490, 620, 20, aGL::Scrollbar::Horizontal, this);
        imageScrollX_->setMaxValue(-100);
        imageScrollX_->valueChanged.connect(canvas_, &Canvas::setImageStartX);

        imageScrollY_ = new aGL::Scrollbar(800, 30, 20, 460, aGL::Scrollbar::Vertical, this);
        imageScrollY_->setMaxValue(-100);
        imageScrollY_->valueChanged.connect(canvas_, &Canvas::setImageStartY);

        tb_ = new Toolbox(Design::LeftPanel::Toolbox::RECT, 45, this);
        createTools();

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
    }



    void MainWindow::applyToolMouseMove(const ToolAction& ta)
    {
        mAssert(tb_->getSelectedTool());
        tb_->getSelectedTool()->onMouseMove(ta);
    }

    void MainWindow::applyToolMousePress(const ToolAction& ta)
    {
        mAssert(tb_->getSelectedTool());
        tb_->getSelectedTool()->onMousePress(ta);
    }

    void MainWindow::applyToolMouseRelease(const ToolAction& ta)
    {
        mAssert(tb_->getSelectedTool());
        tb_->getSelectedTool()->onMouseRelease(ta);
    }

    void MainWindow::createTools()
    {
        tb_->addTool(new tools::Pen{&context_});
        tb_->addTool(new tools::RectFiller{&context_});
        tb_->addTool(new tools::EllipseFiller{&context_});
        tb_->addTool(new tools::Filler(&context_));
        tb_->addTool(new tools::Pippet(&context_));
        tb_->addTool(new tools::Grayer(&context_));
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
