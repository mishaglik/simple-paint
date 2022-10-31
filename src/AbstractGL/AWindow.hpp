#ifndef ABSTRACTGL_AWINDOW_HPP
#define ABSTRACTGL_AWINDOW_HPP
#include <cstdint>
#include <MGeomerty/Geometry.hpp>

#include <AbstractGL/Color.hpp>
#include <AbstractGL/Event.hpp>
#include <AbstractGL/AObject.hpp>
#include <AbstractGL/AText.hpp>
#include <AbstractGL/ARenderSurface.hpp>
#include <AbstractGL/Surface.hpp>
namespace aGL {

    using Point = mgm::Point2i;
    using Rect  = mgm::Rect2<unsigned>;
    

    class Window_;

    class Window : public Surface 
    {
        Window_* wp_;
    public:

        Window(uint32_t width, uint32_t height, const char* title);
        ~Window() override;

        void resize(uint32_t width, uint32_t height) override;
        bool pollEvent(Event& event);
        void drawText    (const Text& text) const override;

        void drawLine    (Point p1, Point p2, Color color = Colors::Black) const override;
        void drawPoint   (Point p, Color color = Colors::Black) const override; 
        void drawRect    (const Rect& rect, Color color = Colors::Black) const override;
        void drawSurf    (Point pt, const RenderSurface& surf) const override;
        void drawSurf    (Point pt, const RenderSurface& surf, const Rect& rect) const override;
        void drawSprite  (Point pt, const Sprite& sprite) const override;
        
        void clear(Color color = Colors::Gray) const override;

        void setActive(bool active = true) const override;
        
        void show();
        void hide();
        void update() const override;
    // Make class non-copyable
        Window(const Window&)             = delete;
        Window& operator= (const Window&) = delete;
    };

}
#endif /* ABSTRACTGL_AWINDOW_HPP */
