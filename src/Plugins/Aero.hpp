#ifndef PLUGINS_AERO_HPP
#define PLUGINS_AERO_HPP
#include "tools.hpp"
#include "Interpolate.hpp"
#include "Brushes.hpp"
using namespace booba;

class Aero : public Tool
{
    Brush::BrushSettings settts_ = {10, 0, 10};
    Brush* brush;
public:
    Aero();
    ~Aero() override { delete  brush; }
    bool isPressed_ = false;
    Point prevDrawn_ = {};
    uint32_t prevLen_ = 10;
    KatmulRom interp_;
    Image* image_ = nullptr;

    void apply(Image* image, const Event* event) override;
    const char* getTexture() override { return "Pen.png";} 
    void buildSetupWidget() override;

    void onMousePress  (const MouseButtonEventData* event);
    void onMouseRelease(const MouseButtonEventData* event);
    void onMouseMove   (const MotionEventData* event);
    void brushDraw(const Point& pt);
};




#endif /* PLUGINS_AERO_HPP */
