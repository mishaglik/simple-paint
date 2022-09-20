#ifndef RAYTRACER_RENDERSPHERE_HPP
#define RAYTRACER_RENDERSPHERE_HPP

#include <Raytracer/RenderObject.hpp>

namespace RTObjs{

class RenderSphere : public RenderObject {
    protected:
    public:
        mgm::Sphere3f sph_;
        bool isSource_ = false;
        aGL::Color color_;
        RenderSphere(const mgm::Point3f& center, double r, bool isSource = false, aGL::Color color = aGL::Colors::White) : 
            sph_(center, r), isSource_(isSource), color_(color) {}
        
        virtual ~RenderSphere() override {}
        

        virtual double getIntersection(const mgm::Ray3f& ray, SurfacePoint* pt = nullptr) const override;
};

}

#endif /* RAYTRACER_RENDERSPHERE_HPP */
