#ifndef PLUGINS_PEN_HPP
#define PLUGINS_PEN_HPP
#include "tools.hpp"
#include "Interpolate.hpp"

using namespace booba;

class Grayer : public Tool
{
public:
    Grayer() {}
    ~Grayer() override {}
    bool isPressed_ = false;
    Point prevDrawn_ = {};
    KatmulRom interp_;
    Image* image_ = nullptr;

    void apply(Image* image, const Event* event) override;
    const char* getTexture() override { return "Pen.png";} 
    void buildSetupWidget() override;

    void onMousePress  (const MouseButtonEventData* event);
    void onMouseRelease(const MouseButtonEventData* event);
    void onMouseMove   (const MotionEventData* event);
};




#endif /* PLUGINS_PEN_HPP */
