#include "GEditor.hpp"
#include <thread>

GEditor* GEditor::app = nullptr;

GEditor::GEditor(int argc, const char* argv[]) :
    aGL::BaseApplication(argc, argv)
{
    app = this;
    mainWindow_ = new mge::MainWindow;
    addWindow(mainWindow_);
    mainWindow_->quited.connect<GEditor>(this, &GEditor::quit);

    sm_ = new aGL::SkinManager;
    sm_->loadSkinset("/home/gms/progs++/vecplot/skins/designed"); //TODO: Better default path.
    mainWindow_->setSkinManager(sm_);
    appState_ = Ready;

    // dialog_ = new aGL::ColorDialog("Test");
}

GEditor::~GEditor()
{
    delete sm_;
}

void GEditor::setCurrentTool(mge::Tool* newTool)
{
    if(currentTool_ == newTool) return;
    toolChanged.emit(newTool);
    currentTool_ = newTool;
}
