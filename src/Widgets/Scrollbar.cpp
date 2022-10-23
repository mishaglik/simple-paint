#include "Scrollbar.hpp"

namespace aGL {
    Scrollbar::Scrollbar(uint32_t x, uint32_t y, uint32_t w, uint32_t h, Orientation orientation, Widget* parent) : 
        Widget({x,y,w,h}, parent), orientation_(orientation)
    {
        if(orientation == Vertical)
        {
            scroll_ = {0, 0, rect_.w, 33};
        }
        else
        {
            scroll_ = {0, 0, 33, rect_.h};
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
            if(orientation_ == Horizontal)
            {
                sprite.setTextureRect({20, 0, 640, 20});
                surface->drawSprite({start, 0}, sprite);
                sprite.setTextureRect({40, 20, 34, 20});
                surface->drawSprite(scroll_.getCornerLL(), sprite);
            }
            else {
                sprite.setTextureRect({0, 20, 20, 460});
                surface->drawSprite({start, 0}, sprite);
                sprite.setTextureRect({20, 40, 20, 34});
                surface->drawSprite(scroll_.getCornerLL(), sprite);
            }
        }
        else {
            surface->clear(0x333e60ff);
            surface->drawRect(scroll_, 0x45a047ff);
        }

        needsRepaint = false;
        return Accepted;
    }

    EventHandlerState Scrollbar::onMouseButtonPressEvent (const Event* event)
    {
        mInfo << "Pressed \n";
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
            int32_t height = orientation_ ? rect_.h : rect_.w;
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
        uint32_t width  = orientation_ ? rect_.w : rect_.h;
        uint32_t height = orientation_ ? rect_.h : rect_.w;
        uint32_t len    = orientation_ ? scroll_.w : scroll_.h;
        ((orientation_ == Orientation::Vertical) ? scroll_.y : scroll_.x) = std::min((width - 2 * height - len), std::max(0u,
            (value_ - minValue_) * (width - 2 * height - len) / (maxValue_ - minValue_))) + height;
    }


    void Scrollbar::update()
    {
        // value_++;
        needsRepaint = 1;
    }
}
