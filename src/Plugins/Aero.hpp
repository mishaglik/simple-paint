#ifndef PLUGINS_AERO_HPP
#define PLUGINS_AERO_HPP
#include "Interpolate.hpp"
#include "Brushes.hpp"
#include "BetPlug.hpp"
using namespace bp;

class Aero : public BTool
{
    Brush::BrushSettings* settts_ = nullptr;
    Brush* brush;
public:
    Aero();
    ~Aero() override {}
    Point prevDrawn_ = {};
    uint64_t prevDrawTime_ = 0;
    uint32_t prevLen_ = 10;
    int32_t density_ = 5;
    KatmulRom interp_;

    const char* getTexture() override { return "Aero.png";} 
    void buildSetupWidget() override;

    void onMousePress  (const MouseButtonEventData* event) override;
    void onMouseRelease(const MouseButtonEventData* event) override;
    void onMouseMove   (const MotionEventData* event) override;
    void onTimerTick   (const TimerEventData* event) override;
    void brushDraw(const Point& pt);
    void setBrushSize(int x) {settts_->size = x;}
    void setOpacity  (int x) {settts_->opacity = x;}
    void setDensity  (int x) {density_ = x;}
};




#endif /* PLUGINS_AERO_HPP */
