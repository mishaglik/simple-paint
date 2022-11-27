#ifndef WIDGETS_DECORATIONS_HPP
#define WIDGETS_DECORATIONS_HPP

#include "AbstractGL/Surface.hpp"
namespace aGL {

    struct DecRect;
    template<class... Args>
    using DecoratorF = DecRect& (*)(DecRect&, Args...);

    struct DecRect
    {
        Surface* surface;
        aGL::Rect rect;

        DecRect(Surface* _surface, const aGL::Rect& _rect) : surface(_surface), rect(_rect) { }
        /* implict */ DecRect(Surface* _surface) : surface(_surface) { rect = surface->getSurfRect();} //I dunno why the fuck i mush do x++; UPD: Fuck you SFML rasterization.
        
        template<class... Args, class... Args2>
        DecRect& decorate(DecoratorF<Args...> decorator, Args2&&... args) { return decorator(*this, std::forward<Args2>(args)...); }        
    };

    namespace Decorations {
        DecRect& border(DecRect& decRect, const aGL::Color& color);
        DecRect& dBorder(DecRect& decRect, const aGL::Color& colorIn, const aGL::Color& colorOut);
    }
}

#endif /* WIDGETS_DECORATIONS_HPP */
