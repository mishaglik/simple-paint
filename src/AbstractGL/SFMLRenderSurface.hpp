#ifndef ABSTRACTGL_SFMLRENDERSURFACE_HPP
#define ABSTRACTGL_SFMLRENDERSURFACE_HPP
#include <SFML/Graphics.hpp>
#include <cassert>
#include <LogUtils/LogUtils.hpp>
#include "ARenderSurface.hpp"
#include "SFMLTexture.hpp"
namespace aGL {

class RenderSurface::RenderSurface_ : public sf::RenderTexture
{
public:
    RenderSurface_(uint32_t w, uint32_t h)
    {
        bool res = create(w, h);
        texture.tp_ = static_cast<Texture::Texture_*>(const_cast<sf::Texture*>(&getTexture()));
        mAssert(res);
    }

    ~RenderSurface_()
    {
        texture.tp_ = nullptr; // Prevent deletion of sf::Texture set up in constructor.
    }

    Texture texture{static_cast<Texture::Texture_*>(nullptr)};
};

}
#endif /* ABSTRACTGL_SFMLRENDERSURFACE_HPP */
