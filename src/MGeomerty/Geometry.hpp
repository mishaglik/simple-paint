#ifndef MGEOMETRY_GEOMETRY_HPP
#define MGEOMETRY_GEOMETRY_HPP

#include <MGeomerty/Point.hpp>
#include <MGeomerty/Rect.hpp>
#include <MGeomerty/Vector.hpp>

namespace mgm{

template<typename num_t>
Vector2<num_t>& operator+(const Vector2<num_t> &v1, const Vector2<num_t>& v2){
    Vector2<num_t> vector = v1;
    return vector += v2;
}


template<typename num_t>
Point2<num_t> operator+=(Point2<num_t>& pt, const Vector2<num_t>& v){
    pt.x += v.x;
    pt.y += v.y;
    return pt;
}

template<typename num_t>
Point2<num_t> operator+(const Point2<num_t>& pt, const Vector2<num_t>& v){
    Point2<num_t> point = pt;
    return pt += v;
}

template<typename num_t>
Vector2<num_t> operator-(const Point2<num_t>& pt1, const Point2<num_t>& pt2){
    return {pt2.x - pt1.x, pt2.y - pt1.y};
}

template<typename num_t>
Vector3<num_t> operator-(const Point3<num_t>& pt1, const Point3<num_t>& pt2){
    return {pt2.x - pt1.x, pt2.y - pt1.y, pt2.z - pt1.z};
}

template<typename num_t>
double radiusLen(Point2<num_t> pt){
    return sqrt(pt.x * pt.x + pt.y * pt.y);
}

template<typename num_t>
double radiusLen(Point3<num_t> pt){
    return sqrt(pt.x * pt.x + pt.y * pt.y + pt.z * pt.z);
}

inline Point3f rotateZ(const Point3f& v, double a){
    return {
         v.x * cos(a) + v.y * sin(a),
        -v.x * sin(a) + v.y * cos(a),
         v.z
        };
}

template<typename num_t>
inline bool contains(const Rect2<num_t>& rect, const Point2<num_t>& pt){
    return 
        pt.x >= rect.x              &&
        pt.x <= rect.x + rect.w     &&
        pt.y >= rect.y              &&
        pt.y <= rect.y + rect.h    ;
}

}
#endif
