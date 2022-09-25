#include "Color.hpp"
#include <algorithm>
#include <iostream>

namespace aGL {

    Color& Color::operator+=(const Color& rhs){
        asRGBA_.r_ = (static_cast<uint32_t>(asRGBA_.r_) + rhs.asRGBA_.r_ > 255) ? 255 : (asRGBA_.r_ + rhs.asRGBA_.r_);
        asRGBA_.g_ = (static_cast<uint32_t>(asRGBA_.g_) + rhs.asRGBA_.g_ > 255) ? 255 : (asRGBA_.g_ + rhs.asRGBA_.g_);
        asRGBA_.b_ = (static_cast<uint32_t>(asRGBA_.b_) + rhs.asRGBA_.b_ > 255) ? 255 : (asRGBA_.b_ + rhs.asRGBA_.b_);
        asRGBA_.a_ = (static_cast<uint32_t>(asRGBA_.a_) + rhs.asRGBA_.a_ > 255) ? 255 : (asRGBA_.a_ + rhs.asRGBA_.a_);
        return *this;
    }

    Color& Color::operator&=(const Color& rhs){
        asRGBA_.r_ = static_cast<uint8_t>((asRGBA_.r_ * static_cast<uint32_t>(rhs.asRGBA_.r_) / 255));
        asRGBA_.g_ = static_cast<uint8_t>((asRGBA_.g_ * static_cast<uint32_t>(rhs.asRGBA_.g_) / 255));
        asRGBA_.b_ = static_cast<uint8_t>((asRGBA_.b_ * static_cast<uint32_t>(rhs.asRGBA_.b_) / 255));
        asRGBA_.a_ = static_cast<uint8_t>((asRGBA_.a_ * static_cast<uint32_t>(rhs.asRGBA_.a_) / 255));
        return *this;
    }

    Color& Color::operator|=(const Color& rhs){
        asRGBA_.r_ = std::max(asRGBA_.r_, rhs.asRGBA_.r_);
        asRGBA_.g_ = std::max(asRGBA_.g_, rhs.asRGBA_.g_);
        asRGBA_.b_ = std::max(asRGBA_.b_, rhs.asRGBA_.b_);
        asRGBA_.a_ = std::max(asRGBA_.a_, rhs.asRGBA_.a_);
        return *this;
    }

    Color operator*(const Color& lhs, double rhs){
        return Color{
        static_cast<uint8_t>(std::min(255., (lhs.r() * rhs))),
        static_cast<uint8_t>(std::min(255., (lhs.g() * rhs))),
        static_cast<uint8_t>(std::min(255., (lhs.b() * rhs))),
        lhs.a(),
        };
    }

    Color operator*(double lhs, const Color& rhs){
        return rhs * lhs;
    }

    mlg::Logger& operator<< (mlg::Logger& out, const Color& color){
        return out << mlg::hex << mlg::setWidth<10> << color.color() << mlg::dec;
    }


}
