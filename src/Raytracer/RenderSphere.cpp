#include "RenderSphere.hpp"


namespace RTObjs {

double RenderSphere::getIntersection(const mgm::Ray3f& ray, SurfacePoint* pt) const {
    mgm::Point3f intersect;

    assert(!sph_.contains(ray.start()));

    if(!mgm::intersect1(ray, sph_, &intersect)){
        return NoIntersection;
    }

    if(pt == nullptr) return (intersect - ray.start()).len();

    pt->point = intersect;
    pt->normal = intersect - sph_.center();
    pt->color = color_;
    pt->reflCoef = 1;
    pt->isSource = isSource_;

    return (intersect - ray.start()).len();
}

}
