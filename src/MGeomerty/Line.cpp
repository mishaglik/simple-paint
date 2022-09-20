#include "Line.hpp"
#include "Geometry.hpp"

namespace mgm {

Line3f::Line3f(const Point3f& p1, const Point3f& p2) : Line3f(p1, p2 - p1) {
    assert(!(p1 == p2));
    
}


bool Line3f::contains(const Point3f &pt) const{
    return (point_ - pt) || dir_;
}

bool isParallel(const Line3f& lhs, const Line3f& rhs){
    return isParallel(lhs.dir(), rhs.dir());
}

bool operator ||(const Line3f& lhs, const Line3f& rhs){
    return isParallel(lhs, rhs);
}

bool operator ==(const Line3f& lhs, const Line3f& rhs){
    return (lhs.dir() || rhs.dir()) && lhs.contains(rhs.point());
}

bool operator ==(const Ray3f& lhs, const Ray3f& rhs){
    return isCollin(lhs.dir(), rhs.dir()) && (lhs.point() == rhs.point());
}

}
