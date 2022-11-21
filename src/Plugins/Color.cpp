#include "Color.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>


Color& Color::operator+=(const Color& rhs)
{
    asRGBA_.r_ = (static_cast<uint32_t>(asRGBA_.r_) + rhs.asRGBA_.r_ > 255) ? 255 : (asRGBA_.r_ + rhs.asRGBA_.r_);
    asRGBA_.g_ = (static_cast<uint32_t>(asRGBA_.g_) + rhs.asRGBA_.g_ > 255) ? 255 : (asRGBA_.g_ + rhs.asRGBA_.g_);
    asRGBA_.b_ = (static_cast<uint32_t>(asRGBA_.b_) + rhs.asRGBA_.b_ > 255) ? 255 : (asRGBA_.b_ + rhs.asRGBA_.b_);
    asRGBA_.a_ = (static_cast<uint32_t>(asRGBA_.a_) + rhs.asRGBA_.a_ > 255) ? 255 : (asRGBA_.a_ + rhs.asRGBA_.a_);
    return *this;
}

Color& Color::operator&=(const Color& rhs)
{
    asRGBA_.r_ = static_cast<uint8_t>((asRGBA_.r_ * static_cast<uint32_t>(rhs.asRGBA_.r_) / 255));
    asRGBA_.g_ = static_cast<uint8_t>((asRGBA_.g_ * static_cast<uint32_t>(rhs.asRGBA_.g_) / 255));
    asRGBA_.b_ = static_cast<uint8_t>((asRGBA_.b_ * static_cast<uint32_t>(rhs.asRGBA_.b_) / 255));
    asRGBA_.a_ = static_cast<uint8_t>((asRGBA_.a_ * static_cast<uint32_t>(rhs.asRGBA_.a_) / 255));
    return *this;
}

Color& Color::operator|=(const Color& rhs)
{
    asRGBA_.r_ = std::max(asRGBA_.r_, rhs.asRGBA_.r_);
    asRGBA_.g_ = std::max(asRGBA_.g_, rhs.asRGBA_.g_);
    asRGBA_.b_ = std::max(asRGBA_.b_, rhs.asRGBA_.b_);
    asRGBA_.a_ = std::max(asRGBA_.a_, rhs.asRGBA_.a_);
    return *this;
}

Color operator*(const Color& lhs, double rhs)
{
    return Color{
    static_cast<uint8_t>(std::min(255., (lhs.r() * rhs))),
    static_cast<uint8_t>(std::min(255., (lhs.g() * rhs))),
    static_cast<uint8_t>(std::min(255., (lhs.b() * rhs))),
    lhs.a(),
    };
}

Color& Color::ablend(const Color& oth)
{
    r(static_cast<uint8_t>(( static_cast<uint32_t>(r()) * (255 - oth.a()) + static_cast<uint32_t>(oth.r()) * oth.a()) / 255));
    g(static_cast<uint8_t>(( static_cast<uint32_t>(g()) * (255 - oth.a()) + static_cast<uint32_t>(oth.g()) * oth.a()) / 255));
    b(static_cast<uint8_t>(( static_cast<uint32_t>(b()) * (255 - oth.a()) + static_cast<uint32_t>(oth.b()) * oth.a()) / 255));
    a(static_cast<uint8_t>(( static_cast<uint32_t>(a()) *            a()  + static_cast<uint32_t>(oth.a()) * (255 - a())) / 255));

    return *this;
}


Color operator*(double lhs, const Color& rhs)
{
    return rhs * lhs;
}

Color operator+ (const Color& lhs, const Color& rhs)
{
    Color res = lhs;
    return res += rhs;
}

Color gammaCorrect(Color col, double gamma)
{
    col.r( static_cast<uint8_t>(255. * std::pow(col.r() / 255., 1 / gamma)));
    col.g( static_cast<uint8_t>(255. * std::pow(col.g() / 255., 1 / gamma)));
    col.b( static_cast<uint8_t>(255. * std::pow(col.b() / 255., 1 / gamma)));
    return col;
}

// void Color::setHSV(uint32_t h, uint8_t s, uint8_t v, uint8_t alpha)


    
uint32_t Color::h() const
{
    int32_t R = r();
    int32_t G = g();
    int32_t B = b();

    int32_t max = std::max(std::max(R, G), B);
    int32_t min = std::min(std::min(R, G), B);
    if(max == min) return 0;


    if(max == R)
    {
        return (60 * (G - B) / (max - min) + ((G < B) ? 360 : 0));
    }
    return (60 * (max == G ? B - R : R - G) / (max - min) + (max == G ? 120 : 240));
}

uint8_t Color::s() const
{
    uint32_t max = std::max(std::max(asRGBA_.r_, asRGBA_.g_), asRGBA_.b_);
    uint32_t min = std::min(std::min(asRGBA_.r_, asRGBA_.g_), asRGBA_.b_);
    return max ? static_cast<uint8_t>(100u * (max - min) / max) : 0;
}

uint8_t Color::v() const
{
    return std::max(std::max(asRGBA_.r_, asRGBA_.g_), asRGBA_.b_) * 100u / 255;
}

void Color::h(uint32_t h)
{
    setHSV(h, s(), v(), a());
}

void Color::s(uint8_t s)
{
    setHSV(h(), s, v(), a());
}

void Color::v(uint8_t v)
{
    setHSV(h(), s(), v, a());
}

