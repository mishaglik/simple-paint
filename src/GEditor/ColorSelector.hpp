#ifndef GEDITOR_COLORSELECTOR_HPP
#define GEDITOR_COLORSELECTOR_HPP

#include "Widgets/Widget.hpp"

namespace mge {
    class ColorSelector : public aGL::Widget
    {
        aGL::Rect foreRect_;
        aGL::Rect backRect_;
        aGL::Rect foreMiniRect_;
        aGL::Rect backMiniRect_;
        aGL::Rect arrowRect_;
    public:
        ColorSelector(const aGL::Rect& rect, aGL::Widget* parent);
        aGL::EventHandlerState onPaintEvent(const aGL::Event*) override;

        aGL::EventHandlerState onMouseButtonPressEvent(const aGL::Event*) override;
    };
}

#endif /* GEDITOR_COLORSELECTOR_HPP */
