#ifndef WIDGETS_SLIDER_HPP
#define WIDGETS_SLIDER_HPP

#include "Widget.hpp"

namespace aGL {

    class Slider : public Widget
    {
    public:
        Slider(const Rect& rect, Widget* parent);
        
        void setMaxValue(int value);
        void setMinValue(int value);
        void setValue(int value);

        void onSkinChange() override;
        EventHandlerState onMouseButtonPressEvent(const Event* ) override;
        EventHandlerState onMouseButtonReleaseEvent(const Event* ) override;
        EventHandlerState onMouseMoveEvent(const Event* ) override;
        EventHandlerState onMouseScrollEvent(const Event* ) override;
        EventHandlerState onKeyPressedEvent(const Event* ) override;
        EventHandlerState onKeyReleasedEvent(const Event* ) override;
        EventHandlerState onMouseLeaveEvent(const Event* ) override;
        EventHandlerState onLoseFocusEvent(const Event* ) override;
        EventHandlerState onPaintEvent(const Event* ) override;
    

        void update() override;
        void setColors(Color backroundColor, Color foregroundColor, Color borderColor, Color textColor);

        Signal<int> valueChanged;
    private:
        int value_ = 0;
        int maxValue_ = 100, minValue_ = 0;
        Color backroundColor_ = 0x505050ff;
        Color foregroundColor_ = 0xbebebebe;
        Color borderColor_ = 0xbebebeff;
        Color textColor_ = 0xddddddff; 
        Text valueText_;

        bool mousePressed_ = false;
        bool keyUpPressed_ = false;
        bool keyDownPressed_ = false;

        Timepoint keyPressStart_;        

        void updateText();

        void pointToValue(const aGL::Point& pt);
    };
}

#endif /* WIDGETS_SLIDER_HPP */
