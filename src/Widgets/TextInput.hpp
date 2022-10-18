#ifndef WIDGETS_TEXTINPUT_HPP
#define WIDGETS_TEXTINPUT_HPP
#include <Widgets/Widget.hpp>

namespace aGL {
    class TextInput : public Widget 
    {
    public:
        TextInput(uint32_t x, uint32_t y, uint32_t w, uint32_t h);

        Signal<const uint32_t*> textEntered;
        Signal<> textUpdated;
        const uint32_t* getText() const { return string_.data(); }
        void setString(const uint32_t* text);

        EventHandlerState onTextEnteredEvent(const Event*) override;
        EventHandlerState onPaintEvent(const Event*) override;
        EventHandlerState onGainFocusEvent(const Event*) override;
        EventHandlerState onLoseFocusEvent(const Event*) override;
    private:
        mvc::Vector<uint32_t> string_;
        Text text_;
    };
}

#endif /* WIDGETS_TEXTINPUT_HPP */
