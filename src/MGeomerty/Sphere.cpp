#include "Sphere.hpp"
#include "Geometry.hpp"

namespace mgm {

bool Sphere3f::contains(const Point3f& pt) const {
    return (pt - center_).len() < r_ - EPS;
}

bool Sphere3f::containsB(const Point3f& pt) const {
    return (pt - center_).len() < r_ + EPS;
}

bool Sphere3f::isOnSurface(const Point3f& pt) const {
    return ((pt - center_).len() - r_) < EPS;
}

bool operator==(const Sphere3f& lhs, const Sphere3f& rhs){
    return lhs.center() == rhs.center() && isZero(lhs.r() - rhs.r());
}


}
