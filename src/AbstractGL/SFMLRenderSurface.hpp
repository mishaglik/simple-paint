#ifndef ABSTRACTGL_SFMLRENDERSURFACE_HPP
#define ABSTRACTGL_SFMLRENDERSURFACE_HPP
#include <SFML/Graphics.hpp>

namespace aGL {

class RenderSurface_ : public sf::RenderTexture{
public:
    RenderSurface_(uint32_t w, uint32_t h){
        create(w, h);
    }
    ~RenderSurface_() override{
        sf::RenderTexture::~RenderTexture();
    }
};

}
#endif /* ABSTRACTGL_SFMLRENDERSURFACE_HPP */
