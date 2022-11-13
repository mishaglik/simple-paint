#ifndef ABSTRACTGL_SFMLTEXT_HPP
#define ABSTRACTGL_SFMLTEXT_HPP

#include "AText.hpp"
#include <SFML/Graphics.hpp>

namespace aGL {

    class Text::Text_ : public sf::Text
    {
        sf::Font font_;
    public:
        Text_(const char* fontName, const char* text, uint32_t x, uint32_t y);
        Text_(const char* fontName, const uint32_t* text, uint32_t x, uint32_t y);

        void setFont(const char* font) { font_.loadFromFile(font); }
    };

}
#endif /* ABSTRACTGL_SFMLTEXT_HPP */
