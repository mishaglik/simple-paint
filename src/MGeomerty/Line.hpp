#ifndef MGEOMERTY_LINE_HPP
#define MGEOMERTY_LINE_HPP
#include "Point.hpp"
#include "Vector.hpp"

namespace mgm {

class Line3f{
    Point3f point_;
    Vector3f dir_;
    public:
        Line3f(const Point3f& pt, const Vector3f& v) : point_(pt), dir_(v) {}
        Line3f(const Point3f& p1, const Point3f& p2);

        bool contains(const Point3f& pt) const;

        const Point3f& point() const {return point_;}
        const Vector3f& dir() const {return dir_;}
};

class Ray3f : public Line3f{
    public:
        Ray3f(const Point3f& pt, const Vector3f& v) : Line3f(pt, v) {}
        Ray3f(const Point3f& p1, const Point3f& p2) : Line3f(p1, p2) {}

        const Point3f& start() const {return point();}
};

bool isParallel(const Line3f& lhs, const Line3f& rhs);  
bool operator ||(const Line3f& lhs, const Line3f& rhs);

bool operator ==(const Line3f& lhs, const Line3f& rhs);
bool operator ==(const Ray3f & lhs, const Ray3f & rhs);

}

#endif /* MGEOMERTY_LINE_HPP */
