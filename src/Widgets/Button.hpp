#ifndef WIDGETS_BUTTON_HPP
#define WIDGETS_BUTTON_HPP
#include "Widget.hpp"

namespace aGL {

    class AbstractButton : public Widget
    {
        static constexpr Color defaultColor_ = 0x232323ff;
        static constexpr Color hoveredColor_ = 0x2a2a2aff;
        static constexpr Color pressedColor_ = 0x353535ff;

        uint32_t verticalMargin   = 13;
        uint32_t horizontalMargin = 5;
        
        Text text_;
        bool pressed_ = false;
        bool hovered_ = false;
        bool togglable_ = false;
        bool state_ = false;
        bool needsRepaint_ = true;

    public:

        AbstractButton(const char* text, uint32_t x, uint32_t y, bool togglable = false);

        Signal<> clicked;
        Signal<> pressed;
        Signal<> released;
        Signal<bool> toggled;
        
        EventHandlerState onMouseButtonPressEvent  (const Event* event) override; 
        EventHandlerState onMouseButtonReleaseEvent(const Event* event) override; 
        EventHandlerState onMouseEnterEvent(const Event* event) override; 
        EventHandlerState onMouseLeaveEvent(const Event* event) override; 
        EventHandlerState onGainFocusEvent(const Event* event) override; 
        EventHandlerState onLoseFocusEvent(const Event* event) override; 
        

        EventHandlerState onPaintEvent(const Event* event) override;

    };

}
#endif /* WIDGETS_BUTTON_HPP */
