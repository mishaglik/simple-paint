#ifndef PLUGINS_CURVES_HPP
#define PLUGINS_CURVES_HPP
#include "BetPlug.hpp"
#include "Interpolate.hpp"

using namespace bp;
class Curve;

class CurveCanvas : public Canvas
{
    static const size_t NPoints = 32;
    constexpr static const Color BackgroundColor = 0x393939ff;

    struct CurvePoint
    {
        bool isActive;
        Point point;
    };
    
    mvc::Array<CurvePoint, NPoints> points_;
    mvc::Array<uint8_t, 101> values_;
    KatmulRom2 kr_;
    uint32_t capturedPoint_ = -1;
public:
    CurveCanvas(int32_t x, int32_t y, uint32_t sz, BTool* parent);
    virtual void onMousePress(const CanvasEventData* )   override;
    virtual void onMouseRelease(const CanvasEventData* ) override;
    virtual void onMouseMove(const CanvasEventData* )    override;
    void reset();
    void repaint();
    void setTension(double tension);

    uint8_t getValue(uint8_t value) { return values_[value]; }
};

class GrainbowCanvas : public Canvas
{
public:
    GrainbowCanvas(Point pt, mgm::Vector2u Size, BTool* parent);
    void fillHorizontal();
    void fillVertical();
};

class Curve : public BTool
{
    CurveCanvas* canvas_ = nullptr;
    void transformImage();
    const char* getTexture() override { return "Pen.png"; }
public:    
    Curve();
    void onMouseMove(const MotionEventData* )         override;
    void onMousePress(const MouseButtonEventData* )   override;
    void onMouseRelease(const MouseButtonEventData* ) override;
    void buildSetupWidget() override;
    void changeTension(int tension);

};



#endif /* PLUGINS_CURVES_HPP */
