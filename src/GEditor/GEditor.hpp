#ifndef GEDITOR_GEDITOR_HPP
#define GEDITOR_GEDITOR_HPP

#include <AbstractGL/Signals.hpp>
#include "ColorDialog/ColorDialog.hpp"
#include "GEditorWindow.hpp"
#include "Widgets/Application.hpp"
#include "Plugins.hpp"
#include "Layers.hpp"
#include <chrono>

namespace mge {
    class Tool;
    struct DrawingContext
    {
        aGL::Color foregroundColor = aGL::Colors::Black;
        aGL::Color backgroundColor = aGL::Colors::White;
    };
}

class GEditor : public aGL::BaseApplication
{
    mge::MainWindow* mainWindow_ = nullptr;
    aGL::ColorDialog* dialog_ = nullptr;

    mge::Tool* currentTool_ = nullptr;
    mvc::Vector<mge::Tool* > tools_;


    void createTools();

public:
    GEditor(int argc, const char* argv[]);
    ~GEditor();

    mvc::Vector<mge::Plugin> plugins_;
    
    mvc::Vector<mge::Layer> layers_;
    aGL::Image* overlayer_ = nullptr;
    uint32_t imageW_ = 0;
    uint32_t imageH_ = 0;
    uint32_t selectedLayer_ = 0;

    const std::chrono::system_clock::time_point startTime_;
    
    static GEditor* app;
    mge::DrawingContext context = {};
    aGL::SkinManager* sm_ = nullptr;

    void setCurrentTool(mge::Tool* newTool);
    mge::Tool* getCurrentTool() const { return currentTool_; }
    aGL::Signal<mge::Tool* > toolChanged;

    void setFgColor(aGL::Color color) { context.foregroundColor = color; }
    void setBgColor(aGL::Color color) { context.backgroundColor = color; }

    void addTool(mge::Tool* tool);
    
    const mvc::Vector<mge::Tool* >& getToolList() const {return tools_;}
};

#endif /* GEDITOR_GEDITOR_HPP */
