#include "Camera.hpp"

namespace RTObjs {
    Camera::Camera(uint32_t w, uint32_t h, double scale) :
        camera_({0, 0, -1000}), canvasCenter_({0,0,0}), base1_(Vec3{1, 0, 0}), base2_({0, 1, 0}), 
        viewVector_(0, 0, 1000), w_(static_cast<int>(w)), h_(static_cast<int>(h))
    {
        base1_ *= scale;   
        base2_ *= scale;
    }

    Point Camera::transform(uint32_t x, uint32_t y) const
    {
        Point pt = canvasCenter_;
        Vec3 v = base1_;
        v *= x;
        pt += v;
        
        v = base2_;
        v *= y;
        pt += v;

        return pt;
    }

    void Camera::moveTo(Point pt)
    {
        camera_ = pt;

        canvasCenter_ = camera_;
        canvasCenter_ += viewVector_;
    }

    void Camera::setViewDirection(Vec3 )
    {
        //Todo Imlement
        return;
    }

    void Camera::setFOV(double fov)
    {
        viewVector_ *= fov / (w_ * h_ * viewVector_.len2());
        canvasCenter_ = camera_;
        canvasCenter_ += viewVector_;
    }

    void Camera::rotate(double angle)
    {
        return; // TODO: Implement
    }
}
