#ifndef PLUGINS_INTERPOLATE_HPP
#define PLUGINS_INTERPOLATE_HPP
#include "Vector.hpp"
#include "tools.hpp"

using Point = mgm::Vector2i;

class Interpolator
{
public:
    virtual ~Interpolator() {}
    virtual void addPoint(Point pt) = 0;
    virtual void reset() = 0;
    virtual Point getPoint(double t) = 0; 
};

class KatmulRom final : public Interpolator
{
    mgm::Vector2f  y_[4] = {};
    mgm::Vector2f dy_[2] = {};
    mgm::Vector2f  a_[4] = {};
    uint8_t points_ = 0;
public:
    KatmulRom();

    ~KatmulRom() override final;

    void addPoint(Point pt) override final;

    void reset() final;

    Point getPoint(double t) final;
};

void drawLine(booba::Image* image, Point p0, Point p1, uint32_t color);


#endif /* PLUGINS_INTERPOLATE_HPP */
