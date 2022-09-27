#include "RenderSphere.hpp"


namespace RTObjs {

    double RenderSphere::getIntersection(const mgm::Ray3f& ray, SurfacePoint* pt) const {
        mgm::Point3f intersect;

        if(!mgm::intersect1(ray, sph_, &intersect)){
            return NoIntersection;
        }

        if(pt == nullptr) return (intersect - ray.start()).len();

        if(sph_.containsB(ray.start())) pt->isInside = true;

        pt->point = intersect;
        pt->normal = mgm::normalize(intersect - sph_.center());
        
        if(pt->isInside) pt->normal *= -1;

        pt->material = &material_;

        return (intersect - ray.start()).len();
    }


    mgm::Point3f RenderSphere::getCenter() const
    {
        return sph_.center();
    }
    aGL::Color   RenderSphere::getColor () const
    {
        return color_;
    }

    void RenderSphere::setMaterial(const Material &material)
    {
        material_ = material;
    }
}
