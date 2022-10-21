#ifndef VECTORPLOT_HPP
#define VECTORPLOT_HPP
#include "Widgets/Widget.hpp"
#include "CoordinateSystem.hpp"
#include "MGeomerty/Point.hpp"
#include "MGeomerty/Vector.hpp"
#include <cstdint>

class VectorPlot : public aGL::Widget, public CoordSystem{
    
    mgm::Vector2f vec_;
    mgm::Point2f startPoint_ = {0, 0};
    double angle_ = 0;
    double speed_ = 0.01;
    bool captured = false;
    void drawBackground() const;
    void drawForeground() const;

public:
    aGL::EventHandlerState onPaintEvent(const aGL::Event*) override;
    
    void update() override;

    VectorPlot(uint32_t x, uint32_t y, uint32_t w, uint32_t h, double minX, double minY, double maxX, double maxY, aGL::Widget* parent = nullptr);
    
    ~VectorPlot() override;

    void setVector(const mgm::Vector2f& vec);
    
    const mgm::Vector2f& getVector() const;
    
    void setAngle(double a);
    void addAngle(double a);

    void setSpeed(double speed);

    void reset() { setAngle(0); setVector({10, 0}); }

    mgm::Vector2f& getVectorRef();
        aGL::EventHandlerState onMouseMoveEvent (const aGL::Event* event) override;
    aGL::EventHandlerState onMouseButtonPressEvent(const aGL::Event* event) override;
    aGL::EventHandlerState onMouseButtonReleaseEvent(const aGL::Event* event) override;

};

#endif /* VECTORPLOT_HPP */
