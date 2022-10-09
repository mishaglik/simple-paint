#ifndef ABSTRACTGL_ARENDERSURFACE_HPP
#define ABSTRACTGL_ARENDERSURFACE_HPP

#include "AText.hpp"
#include "Color.hpp"
#include <AbstractGL/Surface.hpp>
namespace aGL {

    class RenderSurface_;

    class RenderSurface : public Surface
    {
    private:
        RenderSurface_* rsp_;
    public:
        
        RenderSurface(uint32_t w, uint32_t h);
     
        ~RenderSurface() override;
     

        void drawText    (const Text& text) const override;

        void drawLine    (Point p1, Point p2, Color color = Colors::Black) const override;
        void drawPoint   (Point p, Color color = Colors::Black) const override; 
        void drawRect    (const Rect& rect, Color color = Colors::Black) const override;
        void drawSurf    (Point pt, const RenderSurface& surf) const override;

        void clear(Color color = Colors::Gray) const override;
        void resize(uint32_t w, uint32_t h) override;
     
        friend class Window;    // Allow window to access private rsp_;
    };

}
#endif /* ABSTRACTGL_ARENDERSURFACE_HPP */
