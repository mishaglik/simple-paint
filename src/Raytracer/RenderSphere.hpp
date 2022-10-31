#ifndef RAYTRACER_RENDERSPHERE_HPP
#define RAYTRACER_RENDERSPHERE_HPP

#include "Widgets/Label.hpp"
#include <Raytracer/RenderObject.hpp>
#include "Widgets/CollapsibleContainer.hpp"

namespace RTObjs{

    namespace Colors {
        using namespace aGL::Colors;
    }

    class RenderSphere : public RenderObject {
        class RenderSphereEditor;
        protected:
            mgm::Sphere3f sph_;
            Material material_;
        public:
            [[deprecated("Use material")]] aGL::Color color_;
            RenderSphere(const mgm::Point3f& center, double r, const Material& material = MaterialCollection::Mirror) : 
                sph_(center, r), material_(material)
            {
            }
            
            virtual ~RenderSphere() override {}
            

            virtual double getIntersection(const mgm::Ray3f& ray, SurfacePoint* pt = nullptr) const override;

            [[deprecated("Use material")]] virtual mgm::Point3f getCenter() const override;
            [[deprecated("Use material")]] virtual aGL::Color   getColor () const override;
            
            void setMaterial(const Material& material);
            aGL::Widget* getEditorWidget(uint32_t w, aGL::Widget* parent) override;
            virtual Color getSurfaceColor (const Point& pt) const override;

            void setX(int64_t x) {sph_.setCenter(Point(10 * x, sph_.center().y, sph_.center().z)); }
            int64_t getX() {return sph_.center().x / 10; }

    };

    class RenderSphere::RenderSphereEditor : public aGL::CollapsibleContainer
    {
        aGL::Label* label_;
        RenderSphere* sphere_;
    public:
        RenderSphereEditor(RenderSphere* sph, uint32_t w, aGL::Widget* parent);

        void setX(int64_t x) {sphere_->setX(x);}
        
    };

}

#endif /* RAYTRACER_RENDERSPHERE_HPP */
