#include "Scrollbar.hpp"

namespace aGL {
    Scrollbar::Scrollbar(const aGL::Rect& rect, Orientation orientation, uint32_t scrollSize, Widget* parent) : 
        Widget(rect, parent), orientation_(orientation)
    {
        if(orientation == Vertical)
        {
            scroll_ = {0, 0, rect_.w, scrollSize};
        }
        else
        {
            scroll_ = {0, 0, scrollSize, rect_.h};
        }
        value_ = 0;
        updateScrollRect();
    }

    EventHandlerState Scrollbar::onPaintEvent(const Event*)
    {
        updateScrollRect();
        if(skinned())
        {
            const aGL::Texture& tex = sm_->getTexture(texId_);
            Sprite sprite(tex);
            
            int start = 0;
            uint32_t w = orientation_ == Horizontal ? rect_.h : rect_.w; 
            uint32_t sw = orientation_ == Horizontal ? scroll_.w : scroll_.h; 
            if(orientation_ == Horizontal)
            {
                sprite.setTextureRect({w, 0, rect_.w, w});
                surface->drawSprite({start, 0}, sprite);
                sprite.setTextureRect({2 * w, w, sw, w});
                surface->drawSprite(scroll_.getCornerLL(), sprite);
            }
            else {
                sprite.setTextureRect({0, w, w, rect_.h});
                surface->drawSprite({start, 0}, sprite);
                sprite.setTextureRect({w, 2 * w, w, sw});
                surface->drawSprite(scroll_.getCornerLL(), sprite);
            }
        }
        else {
            surface->clear(0x202020ff);
            surface->drawRect(scroll_, 0x5b5b5bff);
        }

        needsRepaint = false;
        return Accepted;
    }

    EventHandlerState Scrollbar::onMouseButtonPressEvent (const Event* event)
    {
        // mInfo << "Pressed \n";
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
            // mInfo << "Released \n";

            captured_ = false;
            return Accepted;
        }
        return Dropped;
    }

    EventHandlerState Scrollbar::onMouseMoveEvent (const Event* event)
    {
        if(captured_)
        {
            // mInfo << "Moved \n";
            int width = orientation_ ? rect_.w : rect_.h;
            int position = orientation_ ? event->mmed.point.x : event->mmed.point.y;
            // int32_t height = orientation_ ? rect_.h : rect_.w;
            int32_t height = 0;
            int32_t len    = orientation_ ? scroll_.w : scroll_.h;
            position = std::max(height + len / 2, std::min(width - height - len / 2, position)) - height - len / 2;

            value_ = position * (maxValue_ - minValue_) / (width - 2 * height - len) + minValue_;
            updateScrollRect();
            valueChanged.emit(value_);
            needsRepaint = true;
            return Accepted;
        }
        return Dropped;
    }

    void Scrollbar::updateScrollRect()
    {
        int32_t width  = orientation_ ? rect_.w : rect_.h;
        // int32_t height = orientation_ ? rect_.h : rect_.w;
        int32_t height = 0;
        int32_t len    = orientation_ ? scroll_.w : scroll_.h;
        ((orientation_ == Orientation::Vertical) ? scroll_.y : scroll_.x) = std::min((width - 2 * height - len), std::max(0,
            (value_ - minValue_) * (width - 2 * height - len) / (maxValue_ - minValue_))) + height;
    }


    void Scrollbar::update()
    {
        // value_++;
        needsRepaint = 1;
    }
}
