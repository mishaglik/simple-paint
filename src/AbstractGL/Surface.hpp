#ifndef ABSTRACTGL_SURFACE_HPP
#define ABSTRACTGL_SURFACE_HPP
#include <AbstractGL/Color.hpp>
#include <MGeomerty/Geometry.hpp>

namespace aGL {
    class Text;
    using Point = mgm::Point2i;
    using Rect  = mgm::Rect2<unsigned>;
    class RenderSurface;
    class Sprite;
    class Surface
    {
    public:
        virtual void drawText    (const Text& text) const = 0;
        virtual void drawLine    (Point p1, Point p2, Color color = Colors::Black) const = 0;
        virtual void drawPoint   (Point p, Color color = Colors::Black) const = 0; 
        virtual void drawRect    (const Rect& rect, Color color = Colors::Black) const = 0;
        virtual void drawSprite  (Point pt, const Sprite& sprite) const = 0;
        virtual void drawSurf    (Point pt, const RenderSurface& surf) const = 0;
        virtual void drawSurf    (Point pt, const RenderSurface& surf, const Rect& rect) const = 0;
        virtual void clear(Color color = Colors::Gray) const = 0;
        virtual void resize(uint32_t width, uint32_t height) = 0;
        virtual void update() const = 0;
        virtual ~Surface() {}
    };
}
#endif /* ABSTRACTGL_SURFACE_HPP */
