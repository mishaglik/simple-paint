#ifndef RAYTRACER_COLORAVG_HPP
#define RAYTRACER_COLORAVG_HPP
#include <AbstractGL/Color.hpp>
#include <cmath>

class AvgColor
{
    uint64_t r_ = 0;
    uint64_t g_ = 0;
    uint64_t b_ = 0;
    uint64_t a_ = 0;
    uint64_t cnt = 0;
public:
    aGL::Color getAvg()
    {
        if(cnt == 0) return aGL::Colors::Black;
        return aGL::Color(
            static_cast<uint8_t>(sqrt(r_ / cnt)),
            static_cast<uint8_t>(sqrt(g_ / cnt)),
            static_cast<uint8_t>(sqrt(b_ / cnt)),
            static_cast<uint8_t>(sqrt(a_ / cnt))
        );
    }

    AvgColor& operator+=(const aGL::Color& col)
    {
        cnt++;
        r_ += col.r() * col.r();
        g_ += col.g() * col.g();
        b_ += col.b() * col.b();
        a_ += col.a() * col.a();
        return *this;
    }

};

#endif /* RAYTRACER_COLORAVG_HPP */
