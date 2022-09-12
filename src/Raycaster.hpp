#ifndef RAYCASTER_HPP
#define RAYCASTER_HPP
#include "AbstractGL/AWindow.hpp"
#include "AbstractGL/Widget.hpp"
#include "CoordinateSystem.hpp"
#include <cstdint>

class Raycaster : public aGL::Widget{
    CoordSystem cs_;
    mgm::Point3f camera_, light_;
    double angle_ = 0;
    public:
        Raycaster(uint32_t x, uint32_t y, uint32_t size);

        void render(const aGL::Window& window) override;
        void addAngle(double angle);

        int handleEvent(const aGL::Event& event) override;
};

#endif /* RAYCASTER_HPP */
