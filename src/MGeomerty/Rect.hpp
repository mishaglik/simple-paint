#ifndef MGEOMERTY_RECT_HPP
#define MGEOMERTY_RECT_HPP
#include "Point.hpp"
namespace mgm{

template<typename num_t> 
struct Rect2{
    num_t x, y, w, h;

    Rect2(num_t x_, num_t y_, num_t w_, num_t h_) : x(x_), y(y_), w(w_), h(h_) {}
    Rect2() : Rect2(0, 0, 0, 0) {}
    
    template<typename T>
    Rect2(const Rect2<T>& oth) : 
        x(static_cast<num_t>(oth.x)),
        y(static_cast<num_t>(oth.y)),
        w(static_cast<num_t>(oth.w)),
        h(static_cast<num_t>(oth.h))
    {}

    Point2<num_t> getCornerLL () const;
    Point2<num_t> getCornerML() const;
    Point2<num_t> getCornerLM () const;
    Point2<num_t> getCornerMM() const;

};

typedef Rect2<unsigned> Rect2u;

template<typename num_t>
Point2<num_t> Rect2<num_t>::getCornerLL () const{
    return {x, y};
}

template<typename num_t>
Point2<num_t> Rect2<num_t>::getCornerML() const{
    return {x + w, y};
}

template<typename num_t>
Point2<num_t> Rect2<num_t>::getCornerLM () const{
    return {x, y + h};
}

template<typename num_t>
Point2<num_t> Rect2<num_t>::getCornerMM() const{
    return {x + w, y + h};
}

}

#endif /* MGEOMERTY_RECT_HPP */
