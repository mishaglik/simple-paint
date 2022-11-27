#include "Slider.hpp"
#include "Decorations.hpp"

namespace aGL {
    Slider::Slider(const Rect& rect, Widget* parent) : Widget(rect, parent), valueText_("0")
    {
        valueText_.setPosition(rect_.w - rect_.w / 5, 0);
        valueText_.setCharacterSize(4 * rect.h / 5);
        valueText_.setColor(textColor_);
    }

    void Slider::setMaxValue(int value)
    {
        maxValue_ = value;
        if(value_ > maxValue_)
        {
            setValue(maxValue_);
        }
    }

    void Slider::setMinValue(int value)
    {
        minValue_ = value;
        if(value_ < minValue_)
        {
            setValue(minValue_);
        }
    }

    void Slider::setValue(int value)
    {
        if(value > maxValue_) value = maxValue_;
        if(value < minValue_) value = minValue_;

        if(value_ != value)
        {
            value_ = value;
            updateText();
            valueChanged.emit(value);
        }
    }

    void Slider::onSkinChange()
    {
        if(sm_)
            valueText_.setFont(sm_->getFont());
    }

    void Slider::pointToValue(const aGL::Point& pt)
    {
        setValue(pt.x * (maxValue_ - minValue_) / rect_.w + minValue_);
    }

    EventHandlerState Slider::onMouseButtonPressEvent(const Event* e)
    {
        if(e->mbed.button == MouseButton::Left)
        {

            pointToValue(e->mbed.point);
            mousePressed_ = true;
            return Accepted;
        }
        return Widget::onMouseButtonPressEvent(e);
    }

    EventHandlerState Slider::onMouseButtonReleaseEvent(const Event* e)
    {
        if(mousePressed_ && e->mbed.button == MouseButton::Left)
        {
            mousePressed_ = false;
            pointToValue(e->mbed.point);
            return Accepted;
        }
        return Widget::onMouseButtonReleaseEvent(e);
    }

    EventHandlerState Slider::onMouseMoveEvent(const Event* e)
    {
        if(mousePressed_)
        {
            pointToValue(e->mmed.point);
        }
        return Widget::onMouseMoveEvent(e);
    }

    EventHandlerState Slider::onMouseScrollEvent(const Event* e)
    {
        setValue(value_ + e->mwed.delta);
        return Accepted;
    }

    EventHandlerState Slider::onKeyPressedEvent(const Event* e)
    {

        if(e->ked.key == KeyboardKey::Up)
        {
            keyUpPressed_ = true;
            keyDownPressed_ = false;
            setValue(value_ + 1);
            return Accepted;
        }
        if(e->ked.key == KeyboardKey::Down)
        {
            keyDownPressed_ = true;
            keyUpPressed_ = false;
            setValue(value_ - 1);
            return Accepted;
        }
        return Widget::onKeyPressedEvent(e);
    }

    EventHandlerState Slider::onKeyReleasedEvent(const Event* e)
    {
        if(e->ked.key == KeyboardKey::Up)
        {
            keyUpPressed_ = false;
            return Accepted;
        }
        if(e->ked.key == KeyboardKey::Down)
        {
            keyDownPressed_ = false;
            return Accepted;
        }
        return Widget::onKeyReleasedEvent(e);
    }

    EventHandlerState Slider::onMouseLeaveEvent(const Event* e)
    {
        mousePressed_ = false;
        return Widget::onMouseLeaveEvent(e);
    }

    EventHandlerState Slider::onLoseFocusEvent(const Event* e)
    {
        keyUpPressed_ = false;
        keyDownPressed_ = false;
        return Widget::onLoseFocusEvent(e);
    }

    EventHandlerState Slider::onPaintEvent(const Event* )
    {
        surface->clear(backroundColor_);
        uint32_t fillWidth = (maxValue_ != minValue_) ? rect_.w * (value_ - minValue_) / (maxValue_ - minValue_) : rect_.w; 
        surface->drawRect({0,0, fillWidth, rect_.h}, foregroundColor_);
        

        DecRect dr(surface);
        dr.decorate(Decorations::border, borderColor_);
        dr.rect = {fillWidth - 2, 1, 4, rect_.h - 2};
        dr.decorate(Decorations::dBorder, 0xff, 0xa0);

        surface->drawText(valueText_);
        
        return Accepted;
    }

    void Slider::update()
    {
    }

    void Slider::updateText()
    {
        std::string s;
        s = std::to_string(value_);
        valueText_.setString(s.c_str());

        valueText_.setPosition(rect_.w - valueText_.getRect().w - 5, 0);
    }

}
