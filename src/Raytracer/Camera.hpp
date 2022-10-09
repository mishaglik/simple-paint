#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP

#include <MGeomerty/Geometry.hpp>

namespace RTObjs {
    using Point = mgm::Point3f;
    using Vec3  = mgm::Vector3f;
    using Ray3  = mgm::Ray3f;

    class Camera
    {
        Point camera_;
        Point canvasCenter_;
        Vec3 base1_, base2_;
        Vec3 viewVector_;    // camera_ + viewVector = canvasCenter_; base1 ^ base2 = canvasCenter;
        int32_t w_, h_;
        double scale_;


    public:
        Camera(uint32_t w, uint32_t h, double scale);
        Ray3 getRay(uint32_t x, uint32_t y) const;
        Point transform(uint32_t x, uint32_t y) const;
        
        void moveTo(Point pt);
        void setViewDirection(Vec3 v);
        void setBaseVectors(Vec3 b1, Vec3 b2);
        void setFOV(double fov);
        void rotate(double angle);

    };
}

#endif /* RAYTRACER_CAMERA_HPP */
