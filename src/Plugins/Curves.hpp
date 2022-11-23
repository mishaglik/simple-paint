#ifndef PLUGINS_CURVES_HPP
#define PLUGINS_CURVES_HPP
#include "BetPlug.hpp"

using namespace bp;
class Curve;

class CurveCanvas : public Canvas
{
    Curve* parent_;
    int capturedPoint = -1;
public:
    CurveCanvas(uint64_t id,  uint32_t w, uint32_t h, Curve* parent);
    virtual void onMousePress(const CanvasEventData* )   override;
    virtual void onMouseRelease(const CanvasEventData* ) override {}
    virtual void onMouseMove(const CanvasEventData* )    override {}
    void repaint();
};

class Curve : public BTool
{
    CurveCanvas* canvas_ = nullptr;
    void transformImage();
    const char* getTexture() override { return "Pen.png"; }
public:
    static const size_t NPoints = 32;
    uint8_t getNewValue(uint8_t value);
    uint32_t getLowerB(Point pt);
    uint32_t getUpperB(Point pt);
    Point points_[NPoints];
    Curve();
    void onMouseMove(const MotionEventData* )         override;
    void onMousePress(const MouseButtonEventData* )   override;
    void onMouseRelease(const MouseButtonEventData* ) override;
    void buildSetupWidget() override;
    void reset();
};



#endif /* PLUGINS_CURVES_HPP */
