#ifndef ABSTRACTGL_WINDOW_HPP
#define ABSTRACTGL_WINDOW_HPP
#include <cstdint>
#include <MGeomerty/Geometry.hpp>

namespace aGL {

using Point = mgm::Point2u;
using Rect  = mgm::Rect<unsigned>;

enum class EventType{
    NoEvent,
    Exit,
    Other,
};

class Event{
public:
    EventType type;
};


class Window_;

struct ColorARGB{
    union{
        struct{
            uint8_t r_, g_, b_, a_;
        };
        uint32_t color;
    };
    ColorARGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : r_(r), g_(g), b_(b), a_(a) {}
    ColorARGB(uint32_t col) : color(col) {}
};

class Window{
    Window_* wp_;
public:
    Window(uint32_t width, uint32_t height, const char* title);
    ~Window();

    void resize(uint32_t width, uint32_t height);
    void drawText    (const char* text);
    Event pollEvent();

    void drawLine    (Point p1, Point p2, ColorARGB color = 0);
    void drawPoint   (Point p, ColorARGB color = 0);
    void drawRect    (const Rect& rect, ColorARGB color = 0);
    void drawTexture ();
    void clear(ColorARGB color = ColorARGB(0,0,0,0));
    void show();
    void hide();
    void update();


// Make class non-copyable
    Window(const Window&)             = delete;
    Window& operator= (const Window&) = delete;
};

}
#endif
