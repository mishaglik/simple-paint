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

    struct Material
    {
        Color color;
        bool isSource = false;
        Color srcColor;
        double fuzzyness;
        double reflCoef;
        double diffCoef;
        double refrCoef; 
        double refrIndex;
    };

    namespace MaterialCollection
    {
        extern const Material Void;
        extern const Material Mirror;
        extern const Material Glass;
        extern const Material Grass;
        extern const Material Sun;
        extern const Material Sky;
    }

    struct SurfacePoint
    {
        Point point;
        Vector normal;
        bool isInside;
        const Material* material;
        [[deprecated("Use material structure")]] Color color;
        [[deprecated("Use material structure")]] bool isSource = false;
        [[deprecated("Use material structure")]] Color srcColor;
        [[deprecated("Use material structure")]] double fuzzyness;
        [[deprecated("Use material structure")]] double reflCoef;
        [[deprecated("Use material structure")]] double diffCoef;
        [[deprecated("Use material structure")]] double refrCoef; 
    };

    class RenderObject{
        protected:
    public:
        [[deprecated("Use material")]] bool isSource_ = false;
        RenderObject(){}

        virtual ~RenderObject() {}
        virtual double getIntersection(const Ray& ray, SurfacePoint* pt = nullptr) const = 0;
        [[deprecated("Use material")]] virtual Point   getCenter() const = 0;
        [[deprecated("Use material")]] virtual Color   getColor () const = 0;

        RenderObject(const RenderObject&) = delete;
        RenderObject& operator=(const RenderObject&) = delete;
    };

}

#endif /* RAYTRACER_RENDEROBJECT_HPP */
