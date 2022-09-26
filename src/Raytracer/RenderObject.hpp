#ifndef RAYTRACER_RENDEROBJECT_HPP
#define RAYTRACER_RENDEROBJECT_HPP
#include <MGeomerty/Geometry.hpp>
#include <AbstractGL/Color.hpp>
#include <limits>
namespace RTObjs {

    const double NoIntersection = 1 / 0.0;

    using Point  = mgm::Point3f;
    using Vector = mgm::Vector3f;
    using Color  = aGL::Color;
    using Ray    = mgm::Ray3f;

    struct SurfacePoint{
        Point point;
        Vector normal;
        Color color;
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
        virtual double getIntersection(const Ray& ray, SurfacePoint* pt = nullptr) const = 0;
        virtual Point   getCenter() const = 0;
        virtual Color   getColor () const = 0;
    };

}

#endif /* RAYTRACER_RENDEROBJECT_HPP */
