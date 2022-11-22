#include "GEditor.hpp"
#include <thread>
// #include "BasicTools.hpp"
#include "GEditor/Plugins.hpp"

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

    mge::importPlugins();

    if(tools_.empty())
    {
        mFatal << "No tools found";
        throw "No tools";
    }

    // createTools();

    // dialog_ = new aGL::ColorDialog("Test");
}

GEditor::~GEditor()
{
    delete sm_;
    for(mge::Tool* tool : tools_ )
    {
        delete tool;
    }
}

void GEditor::setCurrentTool(mge::Tool* newTool)
{
    if(currentTool_ == newTool) return;
    toolChanged.emit(newTool);
    currentTool_ = newTool;
}

void GEditor::addTool(mge::Tool* tool)
{
    tools_.push_back(tool);
}

void GEditor::createTools()
{
    // addTool(new mge::tools::Pen);
    // addTool(new mge::tools::RectFiller);
    // addTool(new mge::tools::EllipseFiller);
    // addTool(new mge::tools::Filler);
    // addTool(new mge::tools::Pippet);
    // addTool(new mge::tools::Grayer);
}
