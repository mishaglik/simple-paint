#include "Color.hpp"
#include <algorithm>

namespace aGL {

Color& Color::operator+=(const Color& rhs){
    asRGBA_.r_ = (asRGBA_.r_ + rhs.asRGBA_.r_ > 255) ? 255 : (asRGBA_.r_ + rhs.asRGBA_.r_);
    asRGBA_.g_ = (asRGBA_.g_ + rhs.asRGBA_.g_ > 255) ? 255 : (asRGBA_.g_ + rhs.asRGBA_.g_);
    asRGBA_.b_ = (asRGBA_.b_ + rhs.asRGBA_.b_ > 255) ? 255 : (asRGBA_.b_ + rhs.asRGBA_.b_);
    asRGBA_.a_ = (asRGBA_.a_ + rhs.asRGBA_.a_ > 255) ? 255 : (asRGBA_.a_ + rhs.asRGBA_.a_);
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

}
