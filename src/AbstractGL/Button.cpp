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
    if(eventFunction_){
        eventFunction_(event);
        return 0;
    }
    return 1;
}

void Button::render(const Window &window){
    window.drawRect(rect_, Colors::DGray);
    Point pt = {rect_.x + rect_.w / 5, rect_.y};
    window.drawText(text_, pt, 0xFF0000FF);
}

}
