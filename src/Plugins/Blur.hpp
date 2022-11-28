#ifndef PLUGINS_BLUR_HPP
#define PLUGINS_BLUR_HPP

#include "BetPlug.hpp"
#include "Brushes.hpp"
#include "Pen.hpp"
class Blur : public bp::Pen
{
    static const int SIGMA_LIMIT = 3;
    mvc::Vector<mvc::Vector<double>> gayss_;

    mvc::Vector<std::pair<Point, Color>> apply_;
    
    Brush::BrushSettings settts_ = {10, 0, 10};
    Brush* brush;

    int sigma_ = 4;
    int degee_ = 50;
    bool sharpening_ = false;
public:
    Blur() { fillGayss(); }
    void onMousePress(const bp::MouseButtonEventData* ) override;
    virtual void buildSetupWidget() override ;
    void applyTool(const Brush::BrushPoint& bp) override;
    const char* getTexture() override {return "Blur.png";}
    void brushDraw(const Point& pt) override;
private:
    void fillGayss();
    void setSigma(int sigma);
    void setDegree(int degree) { degee_ = degree; }
};

#endif /* PLUGINS_BLUR_HPP */
