#ifndef ABSTRACTGL_COLOR_HPP
#define ABSTRACTGL_COLOR_HPP

#include <cstdint>
#include <LogUtils/LogUtils.hpp>

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
        constexpr Color(uint32_t color = 0) : color_(color) {}
        constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : asRGBA_({a, b, g, r}) {}
        
        constexpr Color(const Color& oth) = default;
        constexpr Color& operator =(const Color& oth) = default;

        Color& operator= (uint32_t color) {color_ = color; return *this;}

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

        constexpr void setHSV(uint32_t h, uint8_t s, uint8_t v, uint8_t alpha = 255)
        {
            uint32_t H = h, S = s, V = v;
            uint32_t hIndex = (H / 60) % 6; 
            uint32_t vMin   = (100 - S) * V / 100;
            uint32_t delta  = (V - vMin) * (H % 60) / 60;
            uint32_t vInc   = vMin + delta;
            uint32_t vDec   = V - delta;

            V =    255 * V    / 100;
            vInc = 255 * vInc / 100;
            vDec = 255 * vDec / 100;
            vMin = 255 * vMin / 100;

            switch (hIndex) {
                case 0:
                    asRGBA_.r_ = V;    asRGBA_.g_ = vInc; asRGBA_.b_ = vMin;
                    break;
                case 1:
                    asRGBA_.r_ = vDec; asRGBA_.g_ = V;    asRGBA_.b_ = vMin;
                    break;
                case 2:
                    asRGBA_.r_ = vMin; asRGBA_.g_ = V;    asRGBA_.b_ = vInc;
                    break;
                case 3:
                    asRGBA_.r_ = vMin; asRGBA_.g_ = vDec; asRGBA_.b_ = V;
                    break;
                case 4:
                    asRGBA_.r_ = vInc; asRGBA_.g_ = vMin; asRGBA_.b_ = V;
                    break;
                case 5:
                    asRGBA_.r_ = V;    asRGBA_.g_ = vMin; asRGBA_.b_ = vDec;
                    break;
                default:
                    abort();
            }
            asRGBA_.a_ = alpha;
        }
        
        static constexpr aGL::Color fromHSV(uint32_t h, uint8_t s, uint8_t v, uint8_t alpha = 255)
        {
            aGL::Color ret = {};
            ret.setHSV(h, s, v, alpha);
            return ret;
        }

        uint32_t h() const;
        uint8_t s() const;
        uint8_t v() const;

        void h(uint32_t h);
        void s(uint8_t s);
        void v(uint8_t v);

        Color& operator+= (const Color &rhs);
        Color& operator*= (uint8_t k);
        Color& operator&= (const Color& rhs);
        Color& operator|= (const Color& rhs);
    };


    Color operator* (const Color& lhs, double rhs);
    Color operator* (double lhs, const Color& rhs);

    Color operator+ (const Color& lhs, const Color& rhs); 
    
    Color gammaCorrect(Color col, double gamma);


    mlg::Logger& operator<< (mlg::Logger& out, const Color& color);

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
        const Color Cyan    = 0x00FFFFFF;
    }
}

#endif /* ABSTRACTGL_COLOR_HPP */
