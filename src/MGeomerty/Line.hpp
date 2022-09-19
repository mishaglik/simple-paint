#ifndef MGEOMERTY_LINE_HPP
#define MGEOMERTY_LINE_HPP
#include "Point.hpp"
#include "Vector.hpp"

namespace mgm {

class Line3f{
    Point3f pt_;
    Vector3f dir_;
    public:
        Line3f(const Point3f& pt, const Vector3f& v) : pt_(pt), dir_(v) {}
        Line3f(const Point3f& p1, const Point3f& p2);

};

}

#endif /* MGEOMERTY_LINE_HPP */
