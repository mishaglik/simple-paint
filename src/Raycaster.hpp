#ifndef RAYCASTER_HPP
#define RAYCASTER_HPP
#include "AbstractGL/Widget.hpp"
#include "CoordinateSystem.hpp"
#include <cstdint>

class Raycaster : public aGL::Widget{
    CoordSystem cs_;
    mgm::Point3f camera_, light_;
    double angle_ = 0;
    double speed_ = 0.01;
    bool captured = false;

    public:
        Raycaster(uint32_t x, uint32_t y, uint32_t size);

        void onPaintEvent() const override;
        void addAngle(double angle);

        int handleEvent(const aGL::Event& event) override;
        void update() override;
};

#endif /* RAYCASTER_HPP */
