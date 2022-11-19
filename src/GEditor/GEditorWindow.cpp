#include "GEditorWindow.hpp"
#include "BasicTools.hpp"
#include "ColorDialog/ColorDialog.hpp"
#include "GrandDesign.hpp"
#include "GEditor.hpp"

namespace mge {
    MainWindow::MainWindow() :
        aGL::WWindow(Design::Window::W, Design::Window::H, Design::Window::TITLE)
    {
        backgroundColor_ = Design::ColorPalete::backgroundColor; 
        centralWidget_ = new CentralWidget(Design::MainWidget::RECT, this);

        leftPanel_ = new LeftPanel(Design::LeftPanel::RECT, GEditor::app->getToolList(), this);

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
        if(sm_ && sm_->getFont())
            menubar_->setFont(sm_->getFont());
        menubar_->setCharSize(20);
    }
    
    void MainWindow::onSkinChange()
    {
        if(sm_ && sm_->getFont())
            menubar_->setFont(sm_->getFont());
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
