#include "RenderPlane.hpp"


namespace RTObjs {

    double RenderPlane::getIntersection(const mgm::Ray3f &ray, SurfacePoint* pt) const 
    {
        mgm::Point3f intrsetecton;
        if(mgm::intersect1(plane_, ray, &intrsetecton) == false){
            return NoIntersection;
        }

        if(pt == nullptr)
        {
            return (intrsetecton - ray.start()).len();
        }

        pt->point = intrsetecton;
        pt->normal = plane_.normal();
        if(pt->normal * ray.dir() > 0) pt->normal *= -1;
        
        pt->material = &material_;
        return (intrsetecton - ray.start()).len();
    }


    mgm::Point3f RenderPlane::getCenter() const
    {
        assert(0 && "Plane has no center");
    }

    aGL::Color RenderPlane::getColor() const
    {
        return material_.color;
    }

    void RenderPlane::setMaterial(const Material& material)
    {
        material_ = material;
    }

    aGL::Widget* RenderPlane::getEditorWidget(uint32_t w, aGL::Widget* parent)
    {
        return new RenderPlaneEditor(w, parent);
    }

    RenderPlane::RenderPlaneEditor::RenderPlaneEditor(uint32_t w, aGL::Widget* parent) :
        aGL::ContainerWidget({0, 0, w, 50}, parent)
    {
        label_ = new aGL::Label("Plane", 1, 1, 14, this);
    }


}
