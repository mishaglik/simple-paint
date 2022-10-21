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

    Sprite::Sprite(const Sprite& oth, Rect rect) :
        sp_(new Sprite::Sprite_(*oth.sp_))
    {
        sf::IntRect sfRect = oth.sp_->getTextureRect();
        sp_->setTextureRect({
            sfRect.left + static_cast<int>(rect.x),
            sfRect.top  + static_cast<int>(rect.y),
            static_cast<int>(rect.w),
            static_cast<int>(rect.h),
        });
    }

    Sprite& Sprite::operator=(const Sprite& oth)
    {
        *sp_ = *oth.sp_;
        return *this;
    }

    Rect Sprite::getTextureRect() const
    {
        const sf::IntRect& rect = sp_->getTextureRect(); 
        return Rect{
            static_cast<unsigned>(rect.left),
            static_cast<unsigned>(rect.top),
            static_cast<unsigned>(rect.width),
            static_cast<unsigned>(rect.height),
        };
    }

    Sprite Sprite::crop(Rect& rect)
    {
        return Sprite{*this, rect};
    }
}
