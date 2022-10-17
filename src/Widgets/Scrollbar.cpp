#include "Scrollbar.hpp"

namespace aGL {
    Scrollbar::Scrollbar(uint32_t x, uint32_t y, uint32_t w, uint32_t h, Orientation orientation) : 
        Widget({x,y,w,h}), orientation_(orientation)
    {
        if(orientation == Vertical)
        {
            scroll_ = {0, 0, rect_.w, rect_.h / 10};
        }
        else
        {
            scroll_ = {0, 0, rect_.w /10, rect_.h};
        }
        value_ = 0;
        updateScrollRect();
    }

    EventHandlerState Scrollbar::onPaintEvent(const Event*)
    {
        surface->clear(0x333e60ff);
        updateScrollRect();

        surface->drawRect(scroll_, 0x45a047ff);
        needsRepaint = false;
        return Accepted;
    }

    EventHandlerState Scrollbar::onMouseButtonPressEvent (const Event* event)
    {
        if(event->mbed.button == MouseButton::Left && mgm::contains(scroll_, event->mbed.point))
        {
            captured_ = true;
            return Accepted;
        }
        return Dropped;
    }

    EventHandlerState Scrollbar::onMouseButtonReleaseEvent (const Event* event)
    {
        if(event->mbed.button == MouseButton::Left)
        {
            captured_ = false;
            return Accepted;
        }
        return Dropped;
    }

    EventHandlerState Scrollbar::onMouseMoveEvent (const Event* event)
    {
        if(captured_)
        {
            int width = orientation_ ? rect_.w : rect_.h;
            int position = orientation_ ? event->mmed.point.x : event->mmed.point.y;
            position = std::max(width / 20, std::min(19 * width / 20, position)) - width / 20;

            value_ = position * (maxValue_ - minValue_) / ( 9 * width / 10) + minValue_;
            updateScrollRect();
            valueChanged.emit(value_);
            needsRepaint = true;
            return Accepted;
        }
        return Dropped;
    }

    void Scrollbar::updateScrollRect()
    {
        uint32_t width = orientation_ ? rect_.w : rect_.h;
        ((orientation_ == Orientation::Vertical) ? scroll_.y : scroll_.x) = std::min(width, std::max(0u,
            (value_ - minValue_) * 9 * width / ( (maxValue_ - minValue_) * 10)));
    }


    void Scrollbar::update()
    {   
    }
}
