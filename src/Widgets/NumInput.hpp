#ifndef WIDGETS_NUMINPUT_HPP
#define WIDGETS_NUMINPUT_HPP

#include <Widgets/TextInput.hpp>

namespace aGL {
    class NumInput : public TextInput
    {
    public:
        NumInput(uint32_t x, uint32_t y, uint32_t w, uint32_t h, Widget* parent = nullptr) :
            TextInput(x, y, w, h, parent)
        {
            textUpdated.connect(this, &NumInput::updateNumber);
            textEntered.connect(this, &NumInput::numberEnter);
        }
        
        Signal<int64_t> numberEntered;
        void setNumber(uint64_t num) { number_ = num; updateString(); }

        // EventHandlerState onTextEnteredEvent(const Even* ) override;
        // EventHandlerState onMouseButtonPressEvent(const Event* event) override;
        EventHandlerState onKeyPressedEvent(const Event* event) override;

    private:
        int64_t number_ = 0;
        void updateNumber();
        void updateString();
        void numberEnter(const uint32_t*) { updateNumber(); numberEntered.emit(number_); }
    };
}

#endif /* WIDGETS_NUMINPUT_HPP */
