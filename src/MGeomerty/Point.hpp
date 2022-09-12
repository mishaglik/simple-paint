#ifndef MGEOMETRY_POINT_HPP
#define MGEOMETRY_POINT_HPP
#include <cassert>
#include <math.h>

namespace mgm {

template<typename num_t>
struct Point2{
    num_t x, y;
};

template<typename num_t>
struct Point3{
    num_t x, y, z;
    Point3(num_t x, num_t y, num_t z) : x(x), y(y), z(z) {}
    Point3(const Point2<num_t>& pt) : x(pt.x), y(pt.y), z(0) {}
};

typedef Point2<double>   Point2f;
typedef Point2<int   >   Point2i;
typedef Point2<unsigned> Point2u;

typedef Point3<double>   Point3f;
typedef Point3<int   >   Point3i;
typedef Point3<unsigned> Point3u;
}
#endif
