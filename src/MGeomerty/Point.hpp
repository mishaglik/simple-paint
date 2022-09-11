#ifndef MGEOMETRY_POINT_HPP
#define MGEOMETRY_POINT_HPP
#include <cassert>
#include <math.h>

namespace mgm {

template<typename num_t>
struct Point2{
    num_t x, y;
};

typedef Point2<double>   Point2f;
typedef Point2<int   >   Point2i;
typedef Point2<unsigned> Point2u;

}
#endif
