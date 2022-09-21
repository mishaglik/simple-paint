#ifndef RAYTRACER_RAYTRACER_HPP
#define RAYTRACER_RAYTRACER_HPP
#include <AbstractGL/Widget.hpp>
#include <Raytracer/RenderObject.hpp>
#include <vector>

template<typename T>
using vector = std::vector<T>;

class Raytracer: public aGL::Widget{

    RTObjs::RenderObject** objlist_;
    size_t nObjects;
    
    mgm::Point3f camera_;
    aGL::Color ambient_ = 0x202020ff;

    aGL::Color getRayColor(const mgm::Ray3f& ray, int depth = 0) const;

    bool isRendered = false;

    public:
        Raytracer(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
        ~Raytracer() override;

        void onPaintEvent() const override;
};

#endif /* RAYTRACER_RAYTRACER_HPP */
