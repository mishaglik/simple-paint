#ifndef RAYTRACER_RAYTRACER_HPP
#define RAYTRACER_RAYTRACER_HPP
#include <Widgets/Widget.hpp>
#include <Raytracer/RenderObject.hpp>
#include <Vector/Vector.hpp>
#include <vector>
#include <Raytracer/Camera.hpp>
#include <Raytracer/Scene.hpp>

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
    
    Scene* scene_;
    RTObjs::Camera currentView_;
    uint32_t startX_ = 0;
    uint32_t startY_ = 0;

    [[deprecated("Use scene_")]] Vector<RTObjs::RenderObject*> objlist_;
    [[deprecated("Use currentView_")]] Point camera_;
    
    Color ambient_ = 0x6da6bdff;

    Color getRayColor(const mgm::Ray3f& ray, int depth = 0) const;
    [[deprecated]] Color getLambert(const RTObjs::SurfacePoint& surface) const;
    Color getTrueLambert(const RTObjs::SurfacePoint& surfPoint, int depth, Color surfColor) const;

    bool isRendered = false;

#ifdef RAYTRACER_MULTITHREADING
    struct MulithreadContext
    {
        const Raytracer* rt = nullptr;
        std::mutex xMutex;
        std::mutex drawMutex;
        uint32_t x0 = 0;
        bool finish = false;
    };
    
    static const size_t nThreads = 10;
    mvc::Array<std::thread*, nThreads> threads; // There can be way via std::move but...

    MulithreadContext* multithreadContext_ = nullptr;

    static void raytraceThread(MulithreadContext* context);

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
            .lamberthDepth     = 5,
            .antialiasingLvl   = 2,
            .maxRayRefl        = 20,
            .lamberthReflCost  = 5,
            .lamberthFastEdge  = 12,
            .antialiasMaxShift = .5,
            .gamma             = 1.1,
        };

        [[deprecated]] aGL::Window* wind;

        Raytracer(Scene* scene, uint32_t x, uint32_t y, uint32_t w, uint32_t h, aGL::Widget* parent);
        ~Raytracer() override;

        [[deprecated]] void addObject(RenderObject* object);

        aGL::EventHandlerState onPaintEvent(const aGL::Event* ) override;

        void paintSegment(uint32_t x0, uint32_t w0) const;

    
        void setStartX(int x) {startX_ = x; currentView_.moveTo({static_cast<double>(startX_), static_cast<double>(startY_), -1000}); }
        void setStartY(int y) {startY_ = y; currentView_.moveTo({static_cast<double>(startX_), static_cast<double>(startY_), -1000}); }

        Raytracer(const Raytracer&) = delete;
        Raytracer& operator=(const Raytracer&) = delete;

};

#endif /* RAYTRACER_RAYTRACER_HPP */
