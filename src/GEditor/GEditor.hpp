#ifndef GEDITOR_GEDITOR_HPP
#define GEDITOR_GEDITOR_HPP

#include <AbstractGL/Signals.hpp>
#include "ColorDialog/ColorDialog.hpp"
#include "GEditorWindow.hpp"
#include "Widgets/Application.hpp"

class GEditor : public aGL::BaseApplication
{
    mge::MainWindow* mainWindow_ = nullptr;
    aGL::ColorDialog* dialog_ = nullptr;
    aGL::SkinManager* sm_ = nullptr; 
public:
    GEditor(int argc, const char* argv[]);
    ~GEditor(); 
};


#endif /* GEDITOR_GEDITOR_HPP */
