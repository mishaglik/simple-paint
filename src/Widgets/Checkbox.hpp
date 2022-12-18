#ifndef WIDGETS_CHECKBOX_HPP
#define WIDGETS_CHECKBOX_HPP

#include "Button.hpp"

namespace aGL {
    class Checkbox : public aGL::AbstractButton
    {
    public:
        Checkbox(aGL::Rect rect, aGL::Widget* parent);
        bool getState() const { return pressed_; }
        
        EventHandlerState onPaintEvent(const aGL::Event* event) override;
    };
}

#endif /* WIDGETS_CHECKBOX_HPP */
