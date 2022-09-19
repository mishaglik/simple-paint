#ifndef ABSTRACTGL_AWINDOW_HPP
#define ABSTRACTGL_AWINDOW_HPP
#include <cstdint>
#include <MGeomerty/Geometry.hpp>
#include "Color.hpp"
#include "Event.hpp"
#include "AObject.hpp"
#include "AText.hpp"
#include "ARenderSurface.hpp"

namespace aGL {

using Point = mgm::Point2u;
using Rect  = mgm::Rect2<unsigned>;


class Window_;

class Window : public AObject{
    Window_* wp_;
public:

    Window(uint32_t width, uint32_t height, const char* title);
    ~Window() override;

    void resize(uint32_t width, uint32_t height);
    [[deprecated]] void drawText    (const char* text, Point pt, Color color = 0) const;
    void drawText    (const Text& text) const;
    bool pollEvent(Event& event);

    void drawLine    (Point p1, Point p2, Color color = Colors::Black) const;
    void drawPoint   (Point p, Color color = Colors::Black) const ; 
    void drawRect    (const Rect& rect, Color color = Colors::Black) const;
    void drawSurf    (Point pt, const RenderSurface& surf) const;
    void clear(Color color = Colors::Gray);
    void show();
    void hide();
    void update();

    void handleSignal(int, void* = nullptr) override {}

// Make class non-copyable
    Window(const Window&)             = delete;
    Window& operator= (const Window&) = delete;
};

}
#endif /* ABSTRACTGL_AWINDOW_HPP */
