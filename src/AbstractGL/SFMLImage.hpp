#ifndef ABSTRACTGL_SFMLIMAGE_HPP
#define ABSTRACTGL_SFMLIMAGE_HPP

#include "AImage.hpp"
#include <SFML/Graphics.hpp>

namespace aGL {
    class Image::Image_ : public sf::Image
    {
    };
}

#endif /* ABSTRACTGL_SFMLIMAGE_HPP */
