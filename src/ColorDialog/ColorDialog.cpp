#include "ColorDialog.hpp"

namespace aGL {
    ColorSelector::ColorSelector(aGL::Color start, uint32_t x, uint32_t y, Widget* parent) :
        ContainerWidget({x, y, 300, 300}, parent), currentColor_(start)
    {
        board_ = new ColorBoard(currentColor_, 5, 5, this);
        board_->selected.connect(this, &ColorSelector::setSV);
        
        scroll_ = new ColorScroll(220, 5, this);
        scroll_->hueChanged.connect(this, &ColorSelector::setH);

        exitbutton = new PushButton("Ok", 220, 220, 50, 20, this);
        exitbutton->clicked.connect(this, &ColorSelector::finish);
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

    EventHandlerState ColorSelector::ColorBoard::onMouseButtonReleaseEvent(const Event* e)
    {
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
        return Accepted;
    }

    EventHandlerState ColorSelector::ColorScroll::onMouseButtonPressEvent(const Event* e)
    {
        if(e->mbed.button == aGL::MouseButton::Left)
        {
            uint32_t h = e->mbed.point.y * 360 / rect_.h;
            hueChanged.emit(h);
            return Accepted;
        }
        return Widget::onMouseButtonPressEvent(e);
    }


}
