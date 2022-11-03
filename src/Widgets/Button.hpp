#ifndef WIDGETS_BUTTON_HPP
#define WIDGETS_BUTTON_HPP
#include "Widget.hpp"

namespace aGL {

    class AbstractButton : public Widget
    {
    protected:
        Text text_;
        bool pressed_ = false;
        bool hovered_ = false;
        const bool togglable_ = false;
        const bool hasText_ = true;
        bool state_ = false;
        bool needsRepaint_ = true;

    public:

        AbstractButton(const Rect& rect, const char* text, Widget* parent) : Widget(rect, parent), text_(text) {}
        AbstractButton(const Rect& rect, bool togglable, Widget* parent) : Widget(rect, parent), text_(""), togglable_(togglable), hasText_(false) {}
        virtual ~AbstractButton() override {}

        Signal<> clicked;
        Signal<> pressed;
        Signal<> released;
        Signal<bool> toggled;
        
        EventHandlerState onMouseButtonPressEvent  (const Event* event) override; 
        EventHandlerState onMouseButtonReleaseEvent(const Event* event) override; 
        EventHandlerState onMouseEnterEvent(const Event* event) override; 
        EventHandlerState onMouseLeaveEvent(const Event* event) override; 
        EventHandlerState onGainFocusEvent(const Event* event) override; 
        EventHandlerState onLoseFocusEvent(const Event* event) override; 
        
        void setTextColor(const Color& color);
        void setTextCharacterSize(unsigned size);
        void toggle();
        
        void setString(const char* string)     { needsRepaint_ = true; text_.setString(string); }
        void setString(const uint32_t* string) { needsRepaint_ = true; text_.setString(string); }

    };

    class PushButton : public AbstractButton
    {
        static constexpr Color defaultColor_ = 0x232323ff;
        static constexpr Color hoveredColor_ = 0x2a2a2aff;
        static constexpr Color pressedColor_ = 0x353535ff;

        uint32_t verticalMargin   = 13;
        uint32_t horizontalMargin = 5;

    public:

        PushButton(const char* text, uint32_t x, uint32_t y, Widget* parent = nullptr);
        PushButton(const char* text, uint32_t x, uint32_t y, uint32_t w, uint32_t h, Widget* parent = nullptr);
        ~PushButton() override {}
        
        EventHandlerState onPaintEvent(const Event* event) override;
    };

}
#endif /* WIDGETS_BUTTON_HPP */
