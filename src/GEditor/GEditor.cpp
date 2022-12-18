#include "GEditor.hpp"
#include <thread>
#include "MoveLayer.hpp"
#include "GEditor/Plugins.hpp"

GEditor* GEditor::app = nullptr;

GEditor::GEditor(int argc, const char* argv[]) :
    aGL::BaseApplication(argc, argv), startTime_(std::chrono::high_resolution_clock::now())
{
    app = this;

    aGL::Image* image_ = new aGL::Image("Image.jpg");
    if(!image_->isCreated())
    {
        mError << "Failed to open image\n";
    }

    layers_.push_back({{0, 0, image_->getW(), image_->getH()}, image_, "Background"});
    
    imageW_ = image_->getW();
    imageH_ = image_->getH();

    overlayer_ = new aGL::Image(imageW_, imageH_, 0);

    layers_.push_back({{0, 0, 500, 500}, new aGL::Image(500, 500, 0), "OtherImg"});

    mainWindow_ = new mge::MainWindow;
    addWindow(mainWindow_);
    mainWindow_->quited.connect<GEditor>(this, &GEditor::quit);



    createTools();
    mge::importPlugins(plugins_);

    if(tools_.empty())
    {
        mFatal << "No tools found";
        throw "No tools";
    }

    setCurrentTool(tools_[0]);

    sm_ = new aGL::SkinManager;
    sm_->loadSkinset("./skins/designed"); //TODO: Better default path.
    mainWindow_->setSkinManager(sm_);
    appState_ = Ready;
    // dialog_ = new aGL::ColorDialog("Test");
}

GEditor::~GEditor()
{
    delete sm_;
    for(mge::Tool* tool : tools_ )
    {
        delete tool;
    }
    for(auto layer : layers_)
    {
        delete layer.image;
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
    tool->createPanel();
}

void GEditor::createTools()
{
    addTool(new mge::MoveLayer());
    // addTool(new mge::tools::Pen);
    // addTool(new mge::tools::RectFiller);
    // addTool(new mge::tools::EllipseFiller);
    // addTool(new mge::tools::Filler);
    // addTool(new mge::tools::Pippet);
    // addTool(new mge::tools::Grayer);
}
