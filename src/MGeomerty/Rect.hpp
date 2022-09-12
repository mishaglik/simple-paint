#ifndef MGEOMERTY_RECT_HPP
#define MGEOMERTY_RECT_HPP
#include "Point.hpp"
namespace mgm{

template<typename num_t> 
struct Rect2{
    num_t x, y, w, h;

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
