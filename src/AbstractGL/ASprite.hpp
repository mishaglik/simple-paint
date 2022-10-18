#ifndef ABSTRACTGL_ASPRITE_HPP
#define ABSTRACTGL_ASPRITE_HPP
#include <MGeomerty/Rect.hpp>
namespace aGL {
    using Rect = mgm::Rect2u;
    class Texture;
    class Sprite
    {
        class Sprite_;
        Sprite_* sp_;
        friend class RenderSurface;
        friend class Window;

    public:
        Sprite();
        explicit Sprite(const Texture& texture);
        Sprite(const Texture& texture, Rect rect);

        ~Sprite();

        void setTexture(const Texture& texture);
        void setTextureRect(const Rect& rect);
    };
}

#endif /* ABSTRACTGL_ASPRITE_HPP */
