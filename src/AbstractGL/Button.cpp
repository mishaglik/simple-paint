#include "Button.hpp"

namespace aGL {

Button::Button(const char* text, uint32_t x, uint32_t y) :
    Widget({x, y, 100, 50}), text_(text)
{

}

void Button::setEventFunction(ev_func_t handler){
    eventFunction_ = handler;
}

int Button::handleEvent(const Event& event){
    if(event.type == EventType::MouseButtonPressed && event.mbed.button == MouseButton::Left &&
                                                                        mgm::contains(rect_, event.mbed.point  )){
        pressed_ = true;
    }

    if(pressed_ && event.type == EventType::MouseButtonReleased && event.mbed.button == MouseButton::Left){
        pressed_ = false;
        return mgm::contains(rect_, event.mbed.point);
    }
    return 0;
}

void Button::render(const Window &window){
    window.drawRect(rect_, pressed_ ? pressedColor : defaultColor);
    
    window.drawLine(rect_.getCornerLL(), rect_.getCornerLM(), Colors::LGray);
    window.drawLine(rect_.getCornerLM(), rect_.getCornerMM(), Colors::LGray);
    window.drawLine(rect_.getCornerMM(), rect_.getCornerML(), Colors::LGray);
    window.drawLine(rect_.getCornerML(), rect_.getCornerLL(), Colors::LGray);

    Point pt = {rect_.x + rect_.w / 5, rect_.y};
    
    window.drawText(text_, pt, 0xFF0000FF);
}

}
