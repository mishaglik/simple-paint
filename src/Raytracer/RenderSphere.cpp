#include "RenderSphere.hpp"
#include "Widgets/TextInput.hpp"


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

    RenderSphere::RenderSphereEditor::RenderSphereEditor(uint32_t w, aGL::Widget* parent) :
        aGL::ContainerWidget({0, 0, w, 100}, parent)
    {
        label_ = new aGL::Label("Sphere", 1, 1, 14, this);
        aGL::TextInput* xInput = new aGL::TextInput(0, 30, 50, 30, this);
    }

    aGL::Widget* RenderSphere::getEditorWidget(uint32_t w, aGL::Widget* parent)
    {
        return new RenderSphereEditor(w, parent);
    }

}
