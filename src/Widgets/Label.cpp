#include "Label.hpp"

namespace aGL {
    Label::Label(const char* text, uint32_t x, uint32_t y, uint32_t fontSize, Widget* parent) :
        Widget({x, y, 0, fontSize}, nullptr, parent), text_(text, x, y)
    {
        text_.setCharacterSize(fontSize);
    }

    void Label::setText(const char* text)
    {
        text_.setString(text);
    }

    void Label::setFont(const char*)
    {
        MLG_UIMPLEMENTED
    }

    void Label::setTextColor(const Color& color)
    {
        text_.setColor(color);
    }

    void Label::setTextSize(uint32_t size)
    {
        text_.setCharacterSize(size);
    }

    void Label::render(const Surface* surf) const
    {
        Widget::render(surf);
        surf->drawText(text_);
    }

}
