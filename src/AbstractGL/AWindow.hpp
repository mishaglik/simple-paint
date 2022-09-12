#ifndef ABSTRACTGL_WINDOW_HPP
#define ABSTRACTGL_WINDOW_HPP
#include <cstdint>
#include <MGeomerty/Geometry.hpp>

namespace aGL {

using Point = mgm::Point2u;
using Rect  = mgm::Rect2<unsigned>;

enum class EventType{
    NoEvent,
    Exit,
    Press,
    Other,
};

class Event{
public:
    EventType type;
    union{
        Point pt;
    } data;
};


class Window_;

struct ColorARGB{
    union{
        struct{
            uint8_t a_, b_, g_, r_;
        };
        uint32_t color;
    };
    ColorARGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : r_(r), g_(g), b_(b), a_(a) {}
    ColorARGB(uint32_t col) : color(col) {}
};

inline ColorARGB& operator+=(ColorARGB& lhs, const ColorARGB& rhs){
    lhs.r_ = (lhs.r_ + rhs.r_ > 255) ? 255 : (lhs.r_ + rhs.r_);
    lhs.g_ = (lhs.g_ + rhs.g_ > 255) ? 255 : (lhs.g_ + rhs.g_);
    lhs.b_ = (lhs.b_ + rhs.b_ > 255) ? 255 : (lhs.b_ + rhs.b_);
    lhs.a_ = (lhs.a_ + rhs.a_ > 255) ? 255 : (lhs.a_ + rhs.a_);
    return lhs;
}

namespace Colors {
    const uint32_t White = 0xFFFFFFFF;
    const uint32_t Black = 0x000000FF;
    const uint32_t Gray  = 0xAAAAAAFF;
    const uint32_t DGray = 0x666666FF;

}

class Window{
    Window_* wp_;
public:
    Window(uint32_t width, uint32_t height, const char* title);
    ~Window();

    void resize(uint32_t width, uint32_t height);
    void drawText    (const char* text, Point pt, ColorARGB color = 0) const;
    bool pollEvent(Event& event);

    void drawLine    (Point p1, Point p2, ColorARGB color = 0) const;
    void drawPoint   (Point p, ColorARGB color = 0) const ; 
    void drawRect    (const Rect& rect, ColorARGB color = 0) const;
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
