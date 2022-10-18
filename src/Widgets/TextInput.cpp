#include "TextInput.hpp"

namespace aGL {
    TextInput::TextInput(uint32_t x, uint32_t y, uint32_t w, uint32_t h) : Widget({x, y, w, h}), string_(1, 0), text_("Text here") 
    {
        text_.setCharacterSize(3 * h / 4);
        text_.setColor(Colors::Black);
        // text_.setPosition(0, h/3);
    }

    void setString(const uint32_t* text);

    EventHandlerState TextInput::onTextEnteredEvent(const Event* e) 
    {
        if(focused_) 
        {
            if(e->text == 8) 
            {
                if(string_.size() == 1) return Accepted;
                string_.pop_back();
                string_.back() = 0;
                text_.setString(string_.data());
                return Accepted;
            }
            if(e->text == 13)
            {
                onLoseFocusEvent(nullptr);
                return Accepted;
            }
            
            string_[string_.size() - 1] = e->text;
            string_.push_back(0);
            // mInfo << "str: ";
            // for(uint32_t c : string_) 
            // {
            //     getGlobalLogger() << static_cast<int8_t>(c) << ' ';
            // }
            // getGlobalLogger() << '\n';
            text_.setString(string_.data());

            return Accepted;
        }
        return Dropped;
    }
    
    EventHandlerState TextInput::onPaintEvent(const Event*) 
    {
        surface->clear(Colors::White);
        if(focused_) 
        {
            int32_t w = rect_.w;
            int32_t h = rect_.h;
            surface->drawLine({0, 0}, {0, h}, Colors::Red);
            surface->drawLine({0, h}, {w, h}, Colors::Red);
            surface->drawLine({w, h}, {w, 0}, Colors::Red);
            surface->drawLine({w, 0}, {0, 0}, Colors::Red);
        }
        surface->drawText(text_);
        return Accepted;
    }
    
    EventHandlerState TextInput::onLoseFocusEvent(const Event* e) 
    {
        textEntered.emit(string_.data());
        textUpdated.emit();
        Widget::onLoseFocusEvent(e);
        mInfo << "Unfocused\n";

        return Accepted;
    }

    EventHandlerState TextInput::onGainFocusEvent(const Event* e)
    {
        mInfo << "Focused: " << mlg::endl;
        return Widget::onGainFocusEvent(e);
    }



}
