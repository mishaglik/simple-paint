#ifndef ABSTRACTGL_COLOR_HPP
#define ABSTRACTGL_COLOR_HPP

#include <cstdint>

namespace aGL {

class Color{

    struct ColorBytes{
        uint8_t a_, b_, g_, r_;
    };

    union{
        uint32_t   color_;
        ColorBytes asRGBA_;
    };

public:
    Color(uint32_t color = 0) : color_(color) {}
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : asRGBA_({a, g, b, r}) {}

    Color& operator=(uint32_t color) {color_ = color; return *this;}

    operator uint32_t() const { return color_;}

    uint32_t color() const {return color_;}

    uint8_t r() const {return asRGBA_.r_;}
    uint8_t g() const {return asRGBA_.g_;}
    uint8_t b() const {return asRGBA_.b_;}
    uint8_t a() const {return asRGBA_.a_;}

    void r(uint8_t r) {asRGBA_.r_ = r;}
    void g(uint8_t g) {asRGBA_.g_ = g;}
    void b(uint8_t b) {asRGBA_.b_ = b;}
    void a(uint8_t a) {asRGBA_.a_ = a;}

    Color& operator+= (const Color &rhs);
    Color& operator*= (uint8_t k);
    Color& operator&=(const Color& rhs);


};


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
namespace Colors {
    const Color Transparent = 0;
    const Color White   = 0xFFFFFFFF; 
    const Color Black   = 0x000000FF; 
    const Color Red     = 0xFF0000FF; 
    const Color Green   = 0x00FF00FF; 
    const Color Blue    = 0x0000FFFF; 
    const Color Gray    = 0xA0A0A0FF; 
    const Color DGray   = 0x202020FF; 
    const Color LGray   = 0xD0D0D0FF; 
    const Color Yellow  = 0xFFFF00FF; 
    const Color Magenta = 0xFF00FFFF;
}
#pragma clang diagnostic pop
}

#endif /* ABSTRACTGL_COLOR_HPP */
