#include "Color.hpp"

namespace aGL {

Color& Color::operator+=(const Color& rhs){
    asRGBA_.r_ = (asRGBA_.r_ + rhs.asRGBA_.r_ > 255) ? 255 : (asRGBA_.r_ + rhs.asRGBA_.r_);
    asRGBA_.g_ = (asRGBA_.g_ + rhs.asRGBA_.g_ > 255) ? 255 : (asRGBA_.g_ + rhs.asRGBA_.g_);
    asRGBA_.b_ = (asRGBA_.b_ + rhs.asRGBA_.b_ > 255) ? 255 : (asRGBA_.b_ + rhs.asRGBA_.b_);
    asRGBA_.a_ = (asRGBA_.a_ + rhs.asRGBA_.a_ > 255) ? 255 : (asRGBA_.a_ + rhs.asRGBA_.a_);
    return *this;
}

}
