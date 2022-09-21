#ifndef RAYTRACER_RENDERPLANE_HPP
#define RAYTRACER_RENDERPLANE_HPP

#include <Raytracer/RenderObject.hpp>
#include <MGeomerty/Plane.hpp>

namespace RTObjs {

    class RenderPlane : public RenderObject{
        protected:
            mgm::Plane3f plane_;
            aGL::Color color_;
            bool isSource_ = false;

        public:
            RenderPlane(const mgm::Vector3f& normal, const mgm::Point3f& pt, bool isSource = false, aGL::Color color = aGL::Colors::Green) :
                plane_(normal, pt), color_(color), isSource_(isSource)
                //Kill me with implict conversions bool <-> uint32_t; 
            {
                objName = "Plane";
            } 
            
            virtual ~RenderPlane() override {}
            
            virtual double getIntersection(const mgm::Ray3f& ray, SurfacePoint* pt = nullptr) const override;
    };

}

#endif /* RAYTRACER_RENDERPLANE_HPP */
