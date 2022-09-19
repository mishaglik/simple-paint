#ifndef MGEOMERTY_SPHERE_HPP
#define MGEOMERTY_SPHERE_HPP
#include "Point.hpp"
namespace mgm {

class Sphere3f{
    Point3f center_;
    double r_;
    public:
        Sphere3f(const Point3f& pt, double r): center_(pt), r_(r) {}
        bool hasIn(const Point3f& pt);
        bool hasOnSurf(const Point3f& pt);
};

}

#endif /* MGEOMERTY_SPHERE_HPP */
