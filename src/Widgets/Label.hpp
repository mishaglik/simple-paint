#ifndef WIDGETS_LABEL_HPP
#define WIDGETS_LABEL_HPP

#include "Widgets/Widget.hpp"

namespace aGL {
    class Label : public Widget
    {
    public:
        Label(const char* text, uint32_t x, uint32_t y, uint32_t fontSize = 14, Widget* parent = nullptr);
        ~Label() override {}
        void setText(const char* text);
        void setFont(const char* font);
        void setTextColor(const Color& color);
        void setTextSize(uint32_t size);

        void render(const Surface* surf) const override;
    private:
        Text text_;
    };
}

#endif /* WIDGETS_LABEL_HPP */
