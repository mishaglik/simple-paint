#include <AbstractGL/AText.hpp>
#include "Button.hpp"
#include <iostream>

namespace aGL {

    AbstractButton::AbstractButton(const char* text, uint32_t x, uint32_t y, bool togglable) :
        Widget({x, y, 1, 1}), text_(text, horizontalMargin, verticalMargin + 2), togglable_(togglable)
    {
        text_.setColor(Colors::Red);

        Rect textRect = text_.getRect();
        Widget::resize(textRect.w + 2 * horizontalMargin, textRect.h + 2 * verticalMargin);
    }


    EventHandlerState AbstractButton::onMouseButtonPressEvent(const Event* event) 
    {
        if(event->mbed.button == aGL::MouseButton::Left){
            pressed_ = true;
            pressed.emit();
            needsRepaint_ = true;
            return Accepted;
        }
        return Dropped;
    }

    EventHandlerState AbstractButton::onMouseButtonReleaseEvent(const Event* event)
    {
        if(pressed_ && event->mbed.button == aGL::MouseButton::Left){
            released.emit();
            if(mgm::contains(Rect{0,0, rect_.w, rect_.h}, event->mbed.point)){
                clicked.emit(); //TODO: Ultimate click support
            }
            pressed_ = false;
            needsRepaint_ = true;
            return Accepted;
        }
        return Dropped;
    }

    EventHandlerState AbstractButton::onPaintEvent(const Event* ) 
    {
        if(!needsRepaint_) return Accepted;

        Color drawColor = defaultColor_;
        if(hovered_) drawColor = hoveredColor_;
        if(pressed_) drawColor = pressedColor_;

        surface->drawRect({0, 0, rect_.w, rect_.h}, drawColor); //TODO: Two pictures different transparency
        
        int w = static_cast<int>(rect_.w);
        int h = static_cast<int>(rect_.h);

        surface->drawLine({0, 0}, {0, h}, Colors::LGray);
        surface->drawLine({0, h}, {w, h}, Colors::LGray);
        surface->drawLine({w, h}, {w, 0}, Colors::LGray);
        surface->drawLine({w, 0}, {0, 0}, Colors::LGray);
        
        surface->drawText(text_);
        needsRepaint_ = false;
        return Accepted;
    }

    EventHandlerState AbstractButton::onMouseEnterEvent(const Event*)
    {
        mInfo << mlg::Logger::CoStyle::Green << "Entered" << mlg::endl;
        hovered_ = true;
        needsRepaint_ = true;
        return Accepted;
    }

    EventHandlerState AbstractButton::onMouseLeaveEvent(const Event*)
    {
        mInfo << mlg::Logger::CoStyle::Green << "Leaved\n" << mlg::endl;
        hovered_ = false;
        needsRepaint_ = true;
        return Accepted;
    }

    EventHandlerState AbstractButton::onGainFocusEvent(const Event*)
    {
        return Accepted;
    }

    EventHandlerState AbstractButton::onLoseFocusEvent(const Event*)
    {
        hovered_ = false;
        if(pressed_) released.emit();
        pressed_  = false;
        needsRepaint_ = true;
        return Accepted;
    }
}
