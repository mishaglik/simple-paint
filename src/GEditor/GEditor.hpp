#ifndef GEDITOR_GEDITOR_HPP
#define GEDITOR_GEDITOR_HPP

#include <AbstractGL/Signals.hpp>
#include "ColorDialog/ColorDialog.hpp"
#include "GEditorWindow.hpp"
#include "Widgets/Application.hpp"

namespace mge {
    class Tool;
}

class GEditor : public aGL::BaseApplication
{
    mge::MainWindow* mainWindow_ = nullptr;
    aGL::ColorDialog* dialog_ = nullptr;
    aGL::SkinManager* sm_ = nullptr;

    mge::Tool* currentTool_ = nullptr;

public:
    GEditor(int argc, const char* argv[]);
    ~GEditor();

    static GEditor* app;

    void setCurrentTool(mge::Tool* newTool);
    mge::Tool* getCurrentTool() const { mAssert(currentTool_); return currentTool_; }
    aGL::Signal<mge::Tool* > toolChanged;
};

#endif /* GEDITOR_GEDITOR_HPP */
