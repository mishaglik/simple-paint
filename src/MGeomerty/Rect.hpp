#ifndef MGEOMERTY_RECT_HPP
#define MGEOMERTY_RECT_HPP

namespace mgm{

template<typename num_t> 
struct Rect{
    num_t x, y, w, h;
};

typedef Rect<unsigned> Rect4u;

}
#endif /* MGEOMERTY_RECT_HPP */
