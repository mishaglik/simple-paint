#ifndef ABSTRACTGL_SFMLRENDERSURFACE_HPP
#define ABSTRACTGL_SFMLRENDERSURFACE_HPP
#include <SFML/Graphics.hpp>
#include <cassert>
#include <LogUtils/LogUtils.hpp>

namespace aGL {

class RenderSurface_ : public sf::RenderTexture
{
public:
    RenderSurface_(uint32_t w, uint32_t h)
    {
        mAssert(create(w, h));
    }
};

}
#endif /* ABSTRACTGL_SFMLRENDERSURFACE_HPP */
