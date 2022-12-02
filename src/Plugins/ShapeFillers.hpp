#ifndef PLUGINS_SHAPEFILLERS_HPP
#define PLUGINS_SHAPEFILLERS_HPP

#include "Elpstd/tools.hpp"

using namespace booba;

class RectFiller : public Tool
{
    bool keepPoint = false;
    int32_t prevX_ = 0, prevY_ = 0;

public:
    RectFiller() {}
    ~RectFiller() override {}
    void apply(Image* image, const Event* event) override;
    const char* getTexture() override { return "Rect.png";} 
    void buildSetupWidget() override {}
};

class EllipseFiller : public Tool
{
    bool keepPoint = false;
    int32_t prevX_ = 0, prevY_ = 0;

public:
    EllipseFiller() {}
    ~EllipseFiller() override {}
    void apply(Image* image, const Event* event) override;
    const char* getTexture() override { return "Ellipse.png";} 
    void buildSetupWidget() override {}
};

#endif /* PLUGINS_SHAPEFILLERS_HPP */
