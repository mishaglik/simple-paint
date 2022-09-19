#ifndef ABSTRACTGL_ARENDERSURFACE_HPP
#define ABSTRACTGL_ARENDERSURFACE_HPP

#include "AText.hpp"
#include "Color.hpp"

namespace aGL {

class RenderSurface_;

class RenderSurface{

    RenderSurface_* rsp_;

public:
    RenderSurface(uint32_t w, uint32_t h);
    ~RenderSurface();
    void drawText    (const Text& text) const;

    void drawLine    (Point p1, Point p2, Color color = Colors::Black) const;
    void drawPoint   (Point p, Color color = Colors::Black) const ; 
    void drawRect    (const Rect& rect, Color color = Colors::Black) const;
    void drawSurf    (Point pt, const RenderSurface& surf) const;

    void clear(Color color = Colors::Gray);
    void resize(uint32_t w, uint32_t h);
    friend class Window;
};

}
#endif /* ABSTRACTGL_ARENDERSURFACE_HPP */
