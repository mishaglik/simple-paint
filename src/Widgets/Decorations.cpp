#include "Decorations.hpp"

namespace aGL {
    namespace Decorations {
        DecRect& border(DecRect& decRect, const aGL::Color& color)
        {

            if(decRect.rect.w < 2 || decRect.rect.h < 2)
            {
                decRect.surface->drawRect(decRect.rect, color);
                return decRect;
            }
            decRect.surface->drawHolRect(decRect.rect, color);
            decRect.rect.h -= 2;
            decRect.rect.w -= 2;
            decRect.rect.x++;
            decRect.rect.y++;
            return decRect;
        }

        DecRect& dBorder(DecRect& decRect, const aGL::Color& color1, const aGL::Color& color2)
        {
            return decRect.decorate(border, color2).decorate(border, color1);
        }
    }
}
