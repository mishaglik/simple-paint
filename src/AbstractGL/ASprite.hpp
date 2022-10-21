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
        Sprite(const Texture& texture);             // I, the Author of this shit, being in good health and clear mind allow implict conversion. 
        Sprite(const Texture& texture, Rect rect);
        Sprite(const Sprite& oth);
        Sprite(const Sprite& oth, Rect rect);
        Sprite& operator=(const Sprite& oth);

        ~Sprite();

        void setTexture(const Texture& texture);
        void setTextureRect(const Rect& rect);
        Rect getTextureRect() const;
        Sprite crop(Rect& rect);
    };
}

#endif /* ABSTRACTGL_ASPRITE_HPP */
