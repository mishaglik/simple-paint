#ifndef WIDGETS_APPLICATION_HPP
#define WIDGETS_APPLICATION_HPP
#include "Widgets/WindowWidget.hpp"

namespace aGL {

    class BaseApplication : public SignalObject
    {
    public:
        BaseApplication(int argc, const char* argv[]);
        ~BaseApplication();
        
        BaseApplication(const BaseApplication&) = delete;
        BaseApplication& operator=(const BaseApplication&) = delete;

        static BaseApplication* APP;

        int exec();

        void addWindow(WWindow* w)
        {
            windows_.push_back(w);
            w->quitedP.connect(this, &BaseApplication::onCloseWindow);
        }

        void onCloseWindow(WWindow* w);
        void quit();
    
    private:

        mvc::Vector<WWindow* > windows_;
        mvc::Vector<WWindow* > toDelete_;

        int eventLoop();


    protected:
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

}

#endif /* WIDGETS_APPLICATION_HPP */
