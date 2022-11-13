#ifndef WIDGETS_DECORATIONS_HPP
#define WIDGETS_DECORATIONS_HPP

#include "AbstractGL/ARenderSurface.hpp"
namespace aGL {

    struct DecRect;
    template<class... Args>
    using DecoratorF = DecRect& (*)(DecRect&, Args...);

    struct DecRect
    {
        Surface* surface;
        aGL::Rect rect;

        DecRect(Surface* _surface, const aGL::Rect& _rect) : surface(_surface), rect(_rect) {}
        /* implict */ DecRect(Surface* _surface) : surface(_surface) { rect = surface->getSurfRect(); rect.x++; rect.w--; rect.h--; } //I dunno why the fuck i mush do x++;
        
        template<class... Args>
        DecRect& decorate(DecoratorF<Args...> decorator, Args&&... args) { return decorator(*this, args...); }
    };

    namespace Decorations {
        DecRect& border(DecRect& decRect, const aGL::Color& color);
        DecRect& dBorder(DecRect& decRect, const aGL::Color& colorIn, const aGL::Color& colorOut);
    }
}

#endif /* WIDGETS_DECORATIONS_HPP */
