#ifndef MGEOMERTY_PLANE_HPP
#define MGEOMERTY_PLANE_HPP
#include <MGeomerty/Vector.hpp>
#include <MGeomerty/Point.hpp>
namespace mgm {

class Plane3f{
    Vector3f normal_;
    double dist_;
    
    Plane3f(const Vector3f& normal, double dist) : normal_(normalize(normal)), dist_(dist) {}
public:
    Plane3f(const Vector3f& normal, const Point3f& pt);

    bool contains(const Point3f& pt) const;
    bool contains(const Vector3f& v) const;

    double dist2(const Point3f& pt) const;
    double dist(const Point3f& pt) const;

    const Vector3f& normal() const { return normal_; }
    double d() const { return dist_; }
    void normal(const Vector3f& normal) { normal_ = normalize(normal); }

};

bool operator== (const Plane3f&  lhs, const Plane3f& rhs);
bool operator|| (const Plane3f&  lhs, const Plane3f& rhs);
bool operator|| (const Plane3f&  lhs, const Vector3f& rhs);
bool operator|| (const Vector3f& lhs, const Plane3f& rhs);

}

#endif /* MGEOMERTY_PLANE_HPP */
