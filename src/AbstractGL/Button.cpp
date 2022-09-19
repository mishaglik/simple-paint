#include "Button.hpp"
#include <iostream>

namespace aGL {

Button::Button(const char* text, uint32_t x, uint32_t y) :
    Widget({x, y, 1, 1}), text_(font_, text, horizontalMargin, verticalMargin + 2)
{
    text_.setColor(Colors::Red);

    Rect textRect = text_.getRect();
    Widget::resize(textRect.w + 2 * horizontalMargin, textRect.h + 2 * verticalMargin);
}

void Button::setEventFunction(AObject* eventObject, int eventSignal){
    eventObject_ = eventObject;
    eventSignal_ = eventSignal;
}


int Button::handleEvent(const Event& event){
    if(event.type == EventType::MouseButtonPressed && event.mbed.button == MouseButton::Left &&
                                                                        mgm::contains(rect_, event.mbed.point)){
        pressed_ = true;
    }

    if(pressed_ && event.type == EventType::MouseButtonReleased && event.mbed.button == MouseButton::Left){
        pressed_ = false;
        if(mgm::contains(rect_, event.mbed.point)){
            eventObject_->handleSignal(eventSignal_);
        }
        return 1;
    }
    return 0;
}

void Button::onPaintEvent() const {
    surface->drawRect({0, 0, rect_.w, rect_.h}, pressed_ ? pressedColor_ : defaultColor_); //Todo: Two pictures different transpatency
    
    surface->drawLine({      0,       0}, {      0, rect_.h}, Colors::LGray);
    surface->drawLine({      0, rect_.h}, {rect_.w, rect_.h}, Colors::LGray);
    surface->drawLine({rect_.w, rect_.h}, {rect_.w,       0}, Colors::LGray);
    surface->drawLine({rect_.w,       0}, {      0,       0}, Colors::LGray);
    
    surface->drawText(text_);
}

}
