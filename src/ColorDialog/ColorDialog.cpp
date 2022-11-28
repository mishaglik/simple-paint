#include "ColorDialog.hpp"

namespace aGL {
    ColorSelector::ColorSelector(aGL::Color start, uint32_t x, uint32_t y, Widget* parent) :
        ContainerWidget({x, y, 300, 300}, parent), currentColor_(start)
    {
        board_ = new ColorBoard(currentColor_, 5, 5, this);
        board_->selected.connect(this, &ColorSelector::setSV);
        
        scroll_ = new ColorScroll(220, 5, currentColor_.h(), this);
        scroll_->hueChanged.connect(this, &ColorSelector::setH);

        exitbutton = new PushButton("Ok", 220, 220, 50, 20, this);
        exitbutton->clicked.connect(this, &ColorSelector::finish);
    }

    EventHandlerState ColorSelector::onKeyPressedEvent(const Event* e)
    {
        if(e->ked.key == KeyboardKey::Enter)
        {
            finish();
            return Accepted;
        }
        return ContainerWidget::onKeyPressedEvent(e);
    }


    void ColorSelector::setSV(uint8_t s, uint8_t v)
    {
        currentColor_.setHSV(currentColor_.h(), s, v);
        colorSelected.emit(currentColor_);
    }

    void ColorSelector::setH(uint32_t h)
    {
        currentColor_.h(h);
        board_->setHue(h);
        colorSelected.emit(currentColor_);
    }


    ColorSelector::ColorBoard::ColorBoard(aGL::Color start, uint32_t x, uint32_t y, Widget* parent) :
        Widget({x, y, 201, 201}, parent), hue_(start.h()), sSel_(start.s()), vSel_(start.v())
    {
    }

    EventHandlerState ColorSelector::ColorBoard::onPaintEvent(const Event*)
    {
        surface->clear(aGL::Colors::Black);
        for (uint8_t y = 0; y <= 200; ++y)
        {
            for(uint8_t x = 0; x <= 200; ++x)
            {
                surface->drawPoint({x, y}, Color::fromHSV(hue_, (x) / 2, (200 - y) / 2));
            }
        }

        int32_t x = 2 * sSel_;
        int32_t y = 200 - 2 * vSel_;

        surface->drawLine({x - 1, 0}, Point(x - 1, rect_.h), Colors::LGray);
        surface->drawLine({x + 1, 0}, Point(x + 1, rect_.h), Colors::LGray);

        surface->drawLine({0, y - 1}, Point(rect_.w, y - 1), Colors::LGray);
        surface->drawLine({0, y + 1}, Point(rect_.w, y + 1), Colors::LGray);
        
        surface->drawLine({x, 0}, Point(x, rect_.h), Colors::Black);
        surface->drawLine({0, y}, Point(rect_.w, y), Colors::Black);
        return Accepted;
    }

    EventHandlerState ColorSelector::ColorBoard::onMouseButtonPressEvent(const Event* e)
    {
        if(e->mbed.button == MouseButton::Left)
        {
            pressed_ = true;
            sSel_ = static_cast<uint8_t>(e->mbed.point.x * 100 / rect_.w);
            vSel_ = 100 -  static_cast<uint8_t>(e->mbed.point.y * 100 / rect_.h);
            selected.emit(sSel_, vSel_);
            return Accepted;
        }
        return aGL::Widget::onMouseButtonPressEvent(e);
    }

    EventHandlerState ColorSelector::ColorBoard::onMouseMoveEvent(const Event* e)
    {
        if(pressed_)
        {
            sSel_ = static_cast<uint8_t>(e->mmed.point.x * 100 / rect_.w);
            vSel_ = 100 -  static_cast<uint8_t>(e->mmed.point.y * 100 / rect_.h);
            selected.emit(sSel_, vSel_);
            return Accepted;
        }
        return Widget::onMouseMoveEvent(e);
    }


    EventHandlerState ColorSelector::ColorBoard::onMouseButtonReleaseEvent(const Event* e)
    {
        if(e->mbed.button == MouseButton::Left)
            pressed_ = false;

        return aGL::Widget::onMouseButtonReleaseEvent(e);
    }

    void ColorSelector::ColorBoard::setHue(uint32_t h)
    {
        hue_ = h;
    }

    EventHandlerState ColorSelector::ColorScroll::onPaintEvent(const Event* e)
    {
        // surface->clear(aGL::Colors::Black);
        for(int32_t y = 0; y < rect_.h; ++y)
        {
            surface->drawLine({0, y}, Point(rect_.w, y), Color::fromHSV(360 * y / rect_.h , 100, 100, 255));
        }
        int y = rect_.h * hue_ / 360;
        for(int dy = -1; dy <= 1; ++dy)
        {
            surface->drawLine({0, y + dy}, Point(rect_.w, y + dy), Colors::Black);
        }
        return Accepted;
    }

    EventHandlerState ColorSelector::ColorScroll::onMouseButtonPressEvent(const Event* e)
    {
        if(e->mbed.button == aGL::MouseButton::Left)
        {
            uint32_t h = e->mbed.point.y * 360 / rect_.h;
            hueChanged.emit(h);
            hue_ = h;
            pressed_ = true;
            return Accepted;
        }
        return Widget::onMouseButtonPressEvent(e);
    }


    
    EventHandlerState ColorSelector::ColorScroll::onMouseButtonReleaseEvent(const Event* e)
    {
        if(e->mbed.button == aGL::MouseButton::Left && pressed_)
        {
            pressed_ = false;
            return Accepted;
        }
        return Widget::onMouseButtonReleaseEvent(e);
    }

    EventHandlerState ColorSelector::ColorScroll::onMouseMoveEvent(const Event* e)
    {
        if(pressed_)
        {
            uint32_t h = e->mmed.point.y * 360 / rect_.h;
            hueChanged.emit(h);
            hue_ = h;
            return Accepted;
        }
        return Widget::onMouseMoveEvent(e);
    }

    EventHandlerState ColorSelector::ColorScroll::onMouseLeaveEvent(const Event* e)
    {
        pressed_ = false;
        return Widget::onMouseLeaveEvent(e);
    }

}
