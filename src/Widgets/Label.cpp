#include "Label.hpp"

namespace aGL {
    Label::Label(const char* text, uint32_t x, uint32_t y, uint32_t fontSize, Widget* parent) :
        Widget({x, y, 0, fontSize}, nullptr, parent), text_(text, x, y)
    {
        text_.setCharacterSize(fontSize);
    }

    Label::Label(const char* text, int32_t x, int32_t y, int32_t w, int32_t h, Widget* parent, uint32_t fontSize) :
        Widget(Rect(x, y, w, h), nullptr, parent), text_(text, x, y)
    {
        text_.setCharacterSize(fontSize);
    }

    void Label::setText(const char* text)
    {
        text_.setString(text);
    }

    void Label::setFont(const char* font)
    {
        text_.setFont(font);
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
        // Widget::render(surf);
        surf->drawText(text_);
    }

}
