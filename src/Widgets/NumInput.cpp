#include "NumInput.hpp"

namespace aGL {

    void NumInput::updateNumber()
    {
        number_ = 0;
        for (size_t i = 0; i < string_.size(); ++i)
        {
            if(std::isdigit(string_[i]))
            {
                number_ = 10 * number_ + (string_[i] - '0');
                mInfo << number_ << mlg::endl;
            }
            else {
                string_.resize(i);
                string_.push_back(0);
                return;
            }
        }
                
    }

    EventHandlerState NumInput::onKeyPressedEvent(const Event* event)
    {
        if(event->ked.key == KeyboardKey::Up)
        {
            number_++;
            updateString();
            numberEntered.emit(number_);
            return Accepted;
        }
        if(event->ked.key == KeyboardKey::Down)
        {
            number_--;
            updateString();
            numberEntered.emit(number_);

            return Accepted;
        }

        return TextInput::onKeyPressedEvent(event);
    }

    void NumInput::updateString()
    {
        std::string s = std::to_string(number_);
        setString(s.c_str());
    }

}
