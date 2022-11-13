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
            decRect.surface->drawLine(decRect.rect.getCornerLL(), decRect.rect.getCornerLG(), color);
            decRect.surface->drawLine(decRect.rect.getCornerLG(), decRect.rect.getCornerGG(), color);
            decRect.surface->drawLine(decRect.rect.getCornerGG(), decRect.rect.getCornerGL(), color);
            decRect.surface->drawLine(decRect.rect.getCornerGL(), decRect.rect.getCornerLL(), color);
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
