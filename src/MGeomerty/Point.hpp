#ifndef MGEOMETRY_POINT_HPP
#define MGEOMETRY_POINT_HPP
#include <cassert>
#include <math.h>

namespace mgm {

template<typename num_t>
struct Point2{
    num_t x, y;

    Point2(num_t _x, num_t _y) : x(_x), y(_y) {}
    Point2() : Point2(0, 0) {}
    
    template<typename T>
    Point2(const Point2<T>& pt) : x(pt.x), y(pt.y) {}
};

template<typename num_t>
struct Point3{
    num_t x, y, z;

    Point3(num_t _x, num_t _y, num_t _z) : x(_x), y(_y), z(_z) {}
    Point3() : Point3(0, 0, 0) {}
    Point3(const Point2<num_t>& pt) : x(pt.x), y(pt.y), z(0) {}
    Point3(const Point2<num_t>& pt, num_t _z) : x(pt.x), y(pt.y), z(_z) {}

    template<typename T>
    Point3(const Point3<T>& pt) : x(pt.x), y(pt.y), z(pt.z) {}
};

typedef Point2<double>   Point2f;
typedef Point2<int   >   Point2i;
typedef Point2<unsigned> Point2u;

typedef Point3<double>   Point3f;
typedef Point3<int   >   Point3i;
typedef Point3<unsigned> Point3u;

}
#endif
