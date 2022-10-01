#ifndef RAYTRACER_RAYTRACER_HPP
#define RAYTRACER_RAYTRACER_HPP
#include <AbstractGL/Widget.hpp>
#include <Raytracer/RenderObject.hpp>
#include <Vector/Vector.hpp>
#include <vector>


#define RAYTRACER_MULTITHREADING

#ifdef RAYTRACER_MULTITHREADING
#include <thread>
#include <mutex>
#endif 

class Raytracer: public aGL::Widget{
    template<typename T>
    using Vector = mvc::Vector<T>;

    using Point  = mgm::Point3f;
    using Vec    = mgm::Vector3f;
    using Color  = aGL::Color;
    using Ray    = mgm::Ray3f;

    using RenderObject = RTObjs::RenderObject;

    static Color getSkyGradient(const Vec& v);
    
    Vector<RTObjs::RenderObject*> objlist_;

    Point camera_;
    Color ambient_ = 0x6da6bdff;

    [[deprecated]] uint64_t labertianDepth_ = 5;

    Color getRayColor(const mgm::Ray3f& ray, int depth = 0) const;
    [[deprecated]] Color getLambert(const RTObjs::SurfacePoint& surface) const;
    Color getTrueLambert(const RTObjs::SurfacePoint& surfPoint, int depth) const;

    bool isRendered = false;

#ifdef RAYTRACER_MULTITHREADING
    struct MulithreadContext
    {
        const Raytracer* rt = nullptr;
        std::mutex xMutex;
        std::mutex drawMutex;
        uint32_t x0 = 0;
    };
    
    static const size_t nThreads = 10;
    mvc::Array<std::thread*, nThreads> threads; // There can be way via std::move but...

    MulithreadContext* multithreadContext_ = nullptr;

    [[noreturn]] static void raytraceThread(MulithreadContext* context);

public:
    void render(const aGL::Window& window) const override;
private:
#endif

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
            .lamberthDepth     = 3,
            .antialiasingLvl   = 0,
            .maxRayRefl        = 20,
            .lamberthReflCost  = 5,
            .lamberthFastEdge  = 12,
            .antialiasMaxShift = .5,
            .gamma             = 1.1,
        };

        [[deprecated]] aGL::Window* wind;

        Raytracer(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
        ~Raytracer() override;

        void addObject(RenderObject* object);

        void onPaintEvent() const override;

        void paintSegment(uint32_t x0, uint32_t w0) const;

        Raytracer(const Raytracer&) = delete;
        Raytracer& operator=(const Raytracer&) = delete;

};

#endif /* RAYTRACER_RAYTRACER_HPP */
