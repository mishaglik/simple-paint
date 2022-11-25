#ifndef WIDGETS_DIALOG_HPP
#define WIDGETS_DIALOG_HPP
#include "Application.hpp"
namespace aGL {
 class Dialog : public WWindow
    {
    public:
        Dialog(uint32_t w, uint32_t h, const char* title): WWindow(w, h, title)
        {
            BaseApplication::APP->addWindow(this);
            setTopmost();
        }

    };
}

#endif /* WIDGETS_DIALOG_HPP */
