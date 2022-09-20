#include "Plane.hpp"
#include "Operations.hpp"
namespace mgm {

Plane3f::Plane3f(const Vector3f& normal, const Point3f& pt) : 
    normal_(normalize(normal)), dist_(normal_ * (pt - Point3f{0,0,0})) {
        if(normal_ * (pt - Point3f{0,0,0}) < 0){
            normal_ *= -1;
        }
}

double Plane3f::dist2(const Point3f& pt) const {
    return (normal_ * (pt - Point3f{0,0,0})) - dist_;
}


bool Plane3f::contains(const Point3f& pt) const {
    return isZero(dist2(pt));
}

double Plane3f::dist(const Point3f& pt) const{
    return std::fabs(dist2(pt));
}

bool Plane3f::contains(const Vector3f& v) const {
    return isZero(normal_ * v);
}

bool operator|| (const Plane3f&  lhs, const Plane3f& rhs){
    return (lhs.normal() ^ rhs.normal()).len() < EPS;
}

bool operator== (const Plane3f&  lhs, const Plane3f& rhs){
    return (lhs || rhs) && isZero(lhs.d() - rhs.d());
}

bool operator|| (const Plane3f&  lhs, const Vector3f& rhs){
    return isZero(lhs.normal() * rhs);
}

bool operator|| (const Vector3f& lhs, const Plane3f& rhs){
    return isZero(lhs * rhs.normal());
}

}
