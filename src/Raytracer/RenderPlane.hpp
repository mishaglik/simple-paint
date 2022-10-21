#ifndef RAYTRACER_RENDERPLANE_HPP
#define RAYTRACER_RENDERPLANE_HPP

#include "Widgets/Label.hpp"
#include "Widgets/ContainerWidget.hpp"
#include <Raytracer/RenderObject.hpp>
#include <MGeomerty/Plane.hpp>

namespace RTObjs {

    class RenderPlane : public RenderObject
    {
        class RenderPlaneEditor;
        protected:
            mgm::Plane3f plane_;
            [[deprecated("Use material")]] aGL::Color color_;

            Material material_;

        public:
            RenderPlane(const mgm::Vector3f& normal, const mgm::Point3f& pt, const Material& material = MaterialCollection::Grass) :
                plane_(normal, pt), material_(material)
                //Kill me with implict conversions bool <-> uint32_t; [[deprecated]]
            {
            } 
            
            virtual ~RenderPlane() override {}

            [[deprecated("Use material")]] virtual mgm::Point3f getCenter() const override;
            [[deprecated("Use material")]] virtual aGL::Color getColor () const override;

            void setMaterial(const Material& material);
            
            virtual double getIntersection(const mgm::Ray3f& ray, SurfacePoint* pt = nullptr) const override;
            virtual aGL::Widget* getEditorWidget(uint32_t w, aGL::Widget* parent) override;

    };

    class RenderPlane::RenderPlaneEditor : public aGL::ContainerWidget
    {
        aGL::Label* label_;
    public:
        RenderPlaneEditor(uint32_t w, aGL::Widget* parent);
        
    };

}

#endif /* RAYTRACER_RENDERPLANE_HPP */
