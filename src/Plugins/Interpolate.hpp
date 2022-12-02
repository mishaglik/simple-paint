#ifndef PLUGINS_INTERPOLATE_HPP
#define PLUGINS_INTERPOLATE_HPP
#include "Vector.hpp"
#include "../Vector/Vector.hpp"
#include "Elpstd/tools.hpp"

using Point = mgm::Vector2<int64_t>;

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
public:
    uint8_t points_ = 0;
    KatmulRom();

    ~KatmulRom() override final;

    void addPoint(Point pt) override final;

    void reset() final;

    Point getPoint(double t) final;
};

class KatmulRom2 final : public Interpolator
{
    mvc::Vector<mgm::Vector2f>  points_ = {};
    mgm::Vector2f coefs_[4] = {};
    double  tension_ = 0.5;

    void calcCoef(uint32_t start);
    uint32_t currentStart_ = -1;
public:
    size_t size() const { return points_.size(); }
    KatmulRom2(){}

    ~KatmulRom2() override final{}

    void addPoint(Point pt) override final { points_.push_back(pt); }

    void reset() final;

    Point getPoint(double t) final;

    void setTension(double tension) { tension_ = tension; currentStart_ = -1; }
};

void drawLine(booba::Image* image, Point p0, Point p1, uint32_t color);


#endif /* PLUGINS_INTERPOLATE_HPP */
