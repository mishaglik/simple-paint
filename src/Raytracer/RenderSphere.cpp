#include "RenderSphere.hpp"
#include "Widgets/NumInput.hpp"
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
        
        pt->material = &material_;

        if(pt->isInside) pt->normal *= -1;

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

    RenderSphere::RenderSphereEditor::RenderSphereEditor(RenderSphere* sph, uint32_t w, aGL::Widget* parent) :
        aGL::CollapsibleContainer({0, 0, w, 120}, 20, parent), sphere_(sph)
    {
        label_ = new aGL::Label("Sphere", 1, 1, 14, this);
        label_->setTextColor(aGL::Colors::Blue);
        aGL::NumInput* xInput = new aGL::NumInput(10, 20, 50, 25, this);
        xInput->setNumber(sphere_->getX());
        xInput->numberEntered.connect(this, &RenderSphereEditor::setX);
        xInput->setTextColor(aGL::Colors::Blue);

    }

    aGL::Widget* RenderSphere::getEditorWidget(uint32_t w, aGL::Widget* parent)
    {
        return new RenderSphereEditor(this, w, parent);
    }

  

    Color RenderSphere::getSurfaceColor (const Point& pt) const
    {
        mgm::Vector3f norm = mgm::normalize(pt - sph_.center());

        if(material_.tex != nullptr)
        {
            int32_t x = static_cast<int32_t>((atan2(norm.x, -norm.z) / std::numbers::pi + 1) * 400);
            int32_t y = static_cast<int32_t>((asin(norm.y) / std::numbers::pi + 0.5) * 400);
            mAssert(x >= 0);
            mAssert(y >= 0);
            mAssert(x <= 800);
            mAssert(y <= 400);

            // return aGL::Colors::Red;
            // return Color(255 * x / 800, 0, 0, 0xff);
            x %= 800;
            y %= 400;
            return material_.tex->getPixel(x, y);
        }
        // return norm.y > 0 ? aGL::Colors::Blue : aGL::Colors::Green;
        return aGL::Colors::Black;
    }

}
