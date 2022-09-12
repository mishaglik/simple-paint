#ifndef MGEOMERTY_RECT_HPP
#define MGEOMERTY_RECT_HPP

namespace mgm{

template<typename num_t> 
struct Rect2{
    num_t x, y, w, h;
};

typedef Rect2<unsigned> Rect2u;

}

#endif /* MGEOMERTY_RECT_HPP */
