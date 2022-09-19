#ifndef ABSTRACTGL_SFMLRENDERSURFACE_HPP
#define ABSTRACTGL_SFMLRENDERSURFACE_HPP
#include <SFML/Graphics.hpp>
#include <cassert>

namespace aGL {

class RenderSurface_ : public sf::RenderTexture{
public:
    RenderSurface_(uint32_t w, uint32_t h){
        assert(create(w, h) );
    }
};

}
#endif /* ABSTRACTGL_SFMLRENDERSURFACE_HPP */
