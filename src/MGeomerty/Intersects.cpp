#include "Intersects.hpp"
#include "Operations.hpp"
#include <iostream>
namespace mgm {

    double distBtw(const Line3f& line, const Point3f& pt){
        assert(line.dir().len() > EPS);
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
        if(!sph.contains(*pt)){
            std::cerr << pt->x << ' ' << pt->y << ' ' << pt->z << '\n';
        }
        assert(sph.contains(*pt));
        return true;
    }

    bool intersect1(const Sphere3f& sph, const Ray3f& ray, Point3f* pt){
        double dist = distBtw(ray, sph.center());
        
        if(dist > sph.r() - EPS) return false;

        Vector3f v = normalize(ray.dir());
        Vector3f u = sph.center() - ray.point();

        if(v * u <= 0 && !sph.contains(ray.start())) return false;
        if(pt == nullptr)  return true;

        v *= v * u;
        
        Vector3f h = normalize(v);
        h *= - std::sqrt(fabs(dist * dist - sph.r() * sph.r()));

        v += h;
        
        assert(v * h <= 0);

        *pt = ray.point();
        *pt += v;
        if(!sph.contains(*pt)){
            std::cerr << pt->x << ' ' << pt->y << ' ' << pt->z << '\n';
        }
        assert(sph.contains(*pt));
        return true;
    }

    bool intersect1(const Line3f& line, const Sphere3f& sph, Point3f* pt){
        return intersect1(sph, line, pt);
    }

    bool intersect1(const Ray3f& ray,  const Sphere3f& sph, Point3f* pt){
        return intersect1(sph, ray, pt);
    }

    Vector3f getReflection(const Vector3f& v, const Vector3f& u){
        Vector3f res = normalize(u);
        res *= 2 * (res * v);
        res -= v;
        return res; 
    }

    bool intersect1(const Line3f& line,  const Plane3f& pln, Point3f* pt){
        if(pln || line.dir()) return false;
        if(pt == nullptr) return true;

        Vector3f v = line.dir();
        v *= -pln.dist(line.point()) / (pln.normal() * line.dir());

        *pt = line.point();
        *pt += v;

        return true;
    }


    bool intersect1(const Ray3f&   ray,  const Plane3f& pln, Point3f* pt){
        if(pln || ray.dir()) return false;

        Vector3f v = ray.dir();
        v *= pln.dist(ray.start()) / (pln.normal() * ray.dir());

        if(v * ray.dir() < 0) return false;
        if(pt == nullptr) return true;

        *pt = ray.start();
        *pt += v;

        // assert(pln.contains(*pt));

        return true;
    }
    
    bool intersect1(const Plane3f& pln, const Ray3f&   ray,  Point3f* pt){
        return intersect1(ray, pln, pt);
    }

    bool intersect1(const Plane3f& sph, const Line3f& pln,  Point3f* pt){
        return intersect1(pln, sph, pt);
    }
    
}
