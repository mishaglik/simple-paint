#ifndef MGEOMERTY_RECT_HPP
#define MGEOMERTY_RECT_HPP
#include "Point.hpp"
namespace mgm {

    template<typename num_t>
    struct Rect2
    {
        num_t x, y, w, h;

        Rect2(num_t x_, num_t y_, num_t w_, num_t h_) : x(x_), y(y_), w(w_), h(h_) {}
        Rect2() : Rect2(0, 0, 0, 0) {}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-conversion"    //TODO: think about it
        template<typename T>
        explicit Rect2(const Rect2<T>& oth) :
            x(oth.x),
            y(oth.y),
            w(oth.w),
            h(oth.h)
        {}
#pragma clang diagnostic pop


        Point2<num_t> getCornerLL() const {return {x    , y    };} //FIXME: Cringe naming...
        Point2<num_t> getCornerGL() const {return {x + w, y    };}
        Point2<num_t> getCornerLG() const {return {x    , y + h};}
        Point2<num_t> getCornerGG() const {return {x + w, y + h};}

    };

    using Rect2u = Rect2<unsigned>;

} // namespace mgm

#endif /* MGEOMERTY_RECT_HPP */
