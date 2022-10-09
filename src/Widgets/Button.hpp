#ifndef WIDGETS_BUTTON_HPP
#define WIDGETS_BUTTON_HPP
#include "Widget.hpp"

namespace aGL {

    class Button : public Widget
    {
        const Color defaultColor_ = 0x232323ff;
        const Color pressedColor_ = 0x353535ff;

        uint32_t verticalMargin   = 13;
        uint32_t horizontalMargin = 5;
        
        Text text_;
        bool pressed_ = false;

        AObject* eventObject_ = nullptr;
        int eventSignal_ = 0;

    public:

        Button(const char* text, uint32_t x, uint32_t y);

        void setEventFunction(AObject* eventObject, int eventSignal);
        
        EventHandlerState onMouseButtonPressEvent(const Event* event) override; 

        EventHandlerState onPaintEvent(const Event* event) override;

    };

}
#endif /* WIDGETS_BUTTON_HPP */
