#include "Intersects.hpp"
#include "Geometry.hpp"

namespace mgm {

    double distBtw(const Line3f& line, const Point3f& pt){
        return ((pt - line.point()) ^ line.dir()).len() / (line.dir().len());
    }

    bool intersect1(const Sphere3f& sph, const Line3f& line, Point3f* pt){
        double dist = distBtw(line, sph.center());
        
        if(dist > sph.r()) return false;
        if(pt == nullptr)  return true;

        Vector3f v = normalize(line.dir());
        Vector3f u = sph.center() - line.point();

        v *= v * u;
        
        Vector3f h = normalize(v);
        h *= - std::sqrt(fabs(dist * dist - sph.r() * sph.r()));
        v += h;

        *pt = line.point();
        *pt += v;
        return true;
    }

    bool intersect1(const Sphere3f& sph, const Ray3f&   ray, Point3f* pt){
        return intersect1(sph, static_cast<Line3f>(ray), pt);
    }

}
