#include "SFMLText.hpp"

namespace aGL {

Text::Text_::Text_(const char* fontFilename, const char* text, uint32_t x, uint32_t y){
    if(!font_.loadFromFile(fontFilename)){
        assert(0 && "Font not loaded");
    }
    setFont(font_);
    setString(text);
    setPosition( static_cast<float>(x), 
                 static_cast<float>(y - getCharacterSize() * 0.5));
}

Text::Text(const char* fontName, const char* text, uint32_t x, uint32_t y){
    tp_ = new Text_(fontName, text, x, y);
}

Text::~Text(){
    delete tp_;
}

void Text::setPosition(uint32_t x, uint32_t y){
    tp_->setPosition(
        static_cast<float>(x),
        static_cast<float>(y - tp_->getCharacterSize() * 0.5)
    );
}

void Text::setPosition(const Point& pt){
    setPosition(pt.x, pt.y);
}

void Text::setColor(const Color& color){
    tp_->setFillColor(sf::Color(color));
}

void Text::setStyle(unsigned style){
    tp_->setStyle(style);               // Text styles is equal to SFML
}

void Text::setCharacterSize(unsigned size){
    tp_->setCharacterSize(size);
}

Rect Text::getRect() const {
    sf::FloatRect rect = tp_->getGlobalBounds();

    return {
            static_cast<uint32_t>(rect.left), 
            static_cast<uint32_t>(rect.top), 
            static_cast<uint32_t>(rect.width), 
            static_cast<uint32_t>(rect.height)
           };
}

}
