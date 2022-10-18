#include "SFMLSprite.hpp"

namespace aGL {

    Sprite::Sprite() : sp_(new Sprite_) {}
    Sprite::Sprite(const Texture& texture) : sp_(new Sprite_(texture)) {}
    Sprite::Sprite(const Texture& texture, Rect rect) : sp_(new Sprite_(texture, rect)) {}

    Sprite::~Sprite()
    {
        delete sp_;
        sp_ = nullptr;
    }

    void Sprite::setTexture(const Texture& texture)
    {
        sp_->setTexture(*texture.tp_);
    }

    void Sprite::setTextureRect(const Rect& rect)
    {
        sp_->setTextureRect(getSFMLIntRect(rect));
    }
}
