#ifndef RAYTRACER_RAYTRACER_HPP
#define RAYTRACER_RAYTRACER_HPP
#include <AbstractGL/Widget.hpp>
#include <Raytracer/RenderObject.hpp>
#include <Vector/Vector.hpp>
#include <vector>




class Raytracer: public aGL::Widget{
    template<typename T>
    using Vector = mvc::Vector<T>;

    using Point  = mgm::Point3f;
    using Vec = mgm::Vector3f;
    using Color  = aGL::Color;
    using Ray    = mgm::Ray3f;

    using RenderObject = RTObjs::RenderObject;

    static Color getSkyGradient(const Vec& v);
    
    Vector<RTObjs::RenderObject*> objlist_;

    Point camera_;
    Color ambient_ = 0x202020ff;

    uint64_t labertianDepth_ = 5;

    Color getRayColor(const mgm::Ray3f& ray, int depth = 0) const;
    Color getLambert(const RTObjs::SurfacePoint& surface) const;
    Color getTrueLambert(const RTObjs::SurfacePoint& surfPoint, int depth) const;

    bool isRendered = false;

    public:

        struct QualitySettings
        {
            uint64_t lamberthDepth;
            uint64_t antialiasingLvl;
            int      maxRayRefl;
            int      lamberthReflCost;
            int      lamberthFastEdge;
            double   antialiasMaxShift;
            double   gamma;
        };

        QualitySettings qS_
        {
            .lamberthDepth     = 40,
            .antialiasingLvl   = 40,
            .maxRayRefl        = 20,
            .lamberthReflCost  = 5,
            .lamberthFastEdge  = 12,
            .antialiasMaxShift = 0.5,
            .gamma             = 1.5,
        };

        aGL::Window* wind; //HACK

        Raytracer(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
        ~Raytracer() override;

        void addObject(RenderObject* object);

        void onPaintEvent() const override;

        Raytracer(const Raytracer&) = delete;
        Raytracer& operator=(const Raytracer&) = delete;

};

#endif /* RAYTRACER_RAYTRACER_HPP */
