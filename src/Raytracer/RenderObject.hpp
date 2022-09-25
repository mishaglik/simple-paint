#ifndef RAYTRACER_RENDEROBJECT_HPP
#define RAYTRACER_RENDEROBJECT_HPP
#include <MGeomerty/Geometry.hpp>
#include <AbstractGL/Color.hpp>
#include <limits>
namespace RTObjs {

    const double NoIntersection = 1 / 0.0;

    struct SurfacePoint{
        mgm::Point3f point;
        mgm::Vector3f normal;
        aGL::Color color;
        bool isSource = false;
        double reflCoef;
        double refrCoef;
    };

    class RenderObject{
        protected:
        const char* objName = "";
    public:
        bool isSource_ = false;
        virtual ~RenderObject() {}
        virtual double getIntersection(const mgm::Ray3f& ray, SurfacePoint* pt = nullptr) const = 0;
        virtual mgm::Point3f getCenter() const = 0;
        virtual aGL::Color   getColor () const = 0;
    };

}

#endif /* RAYTRACER_RENDEROBJECT_HPP */
