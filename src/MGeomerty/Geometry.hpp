#ifndef MGEOMETRY_GEOMETRY_HPP
#define MGEOMETRY_GEOMETRY_HPP

#include <MGeomerty/Point.hpp>
#include <MGeomerty/Rect.hpp>
#include <MGeomerty/Vector.hpp>

namespace mgm{

template<typename num_t>
Point2<num_t> operator+(const Point2<num_t>& pt, const Vector2<num_t>& v){
    return {pt.x + v.x, pt.y + v.y};
}

template<typename num_t>
Point2<num_t> operator+=(Point2<num_t>& pt, const Vector2<num_t>& v){
    pt.x += v.x;
    pt.y += v.y;
    return pt;
}

template<typename num_t>
Vector2<num_t> operator-(const Point2<num_t>& pt1, const Point2<num_t>& pt2){
    return {pt2.x - pt1.x, pt2.y - pt1.y};
}

}
#endif
