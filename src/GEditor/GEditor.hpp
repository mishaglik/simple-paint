#ifndef GEDITOR_GEDITOR_HPP
#define GEDITOR_GEDITOR_HPP

#include <AbstractGL/Signals.hpp>
#include "GEditorWindow.hpp"

class GEditor : public aGL::SignalObject
{
    mge::MainWindow* mainWindow_ = nullptr;
    aGL::SkinManager* sm_ = nullptr; 
public:
    GEditor(int argc, const char* argv[]);
    ~GEditor();

    GEditor(const GEditor&) = delete;
    GEditor& operator=(const GEditor&) = delete;

    int exec();
private:
    int eventLoop();

    void quit();

    enum AppState
    {
        Initializing,
        Ready,
        Runnig,
        Stopping,
        Died,
        ERROR,
    };

    AppState appState_ = Initializing;

};

#endif /* GEDITOR_GEDITOR_HPP */
