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
        menubar_->setTextColor(Design::ColorPalete::TextColor);
    }
    
    void MainWindow::createTools()
    {
        DrawingContext* context = &GEditor::app->context;

        tools_.push_back(new tools::Pen{context});
        tools_.push_back(new tools::RectFiller{context});
        tools_.push_back(new tools::EllipseFiller{context});
        tools_.push_back(new tools::Filler(context));
        tools_.push_back(new tools::Pippet(context));
        tools_.push_back(new tools::Grayer(context));
    }

    void MainWindow::colorSelect()
    {
        aGL::ColorDialog* dialog = new aGL::ColorDialog("Fore color", GEditor::app->context.foregroundColor);
        dialog->Window::show();
        dialog->finished.connect(this, &MainWindow::setForegroundColor);
    }

    void MainWindow::setForegroundColor(aGL::Color color)
    {
        GEditor::app->context.foregroundColor = color;
    }
}
