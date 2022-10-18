#ifndef ABSTRACTGL_SFMLTEXTURE_HPP
#define ABSTRACTGL_SFMLTEXTURE_HPP
#include "ATexture.hpp"
#include <SFML/Graphics.hpp>

namespace aGL {

    class Texture::Texture_ : public sf::Texture
    {
    public:
        Texture_()                             = default;
        Texture_(const Texture_& t)            = default;
        Texture_& operator=(const Texture_& t) = default;
        ~Texture_()                            = default;
    };
}

#endif /* ABSTRACTGL_SFMLTEXTURE_HPP */
