#include "GEditor.hpp"
#include <thread>

GEditor::GEditor(int argc, const char* argv[]) :
    aGL::BaseApplication(argc, argv)
{

    mainWindow_ = new mge::MainWindow;
    addWindow(mainWindow_);
    mainWindow_->quited.connect<GEditor>(this, &GEditor::quit);

    sm_ = new aGL::SkinManager;
    sm_->loadSkinset("/home/gms/progs++/vecplot/skins/minimalistic"); //TODO: Better default path.
    mainWindow_->setSkinManager(sm_);
    appState_ = Ready;

    // dialog_ = new aGL::ColorDialog("Test");
}

GEditor::~GEditor()
{
    delete sm_;
}
