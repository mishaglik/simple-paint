#ifndef COORDINATESYSTEM_HPP
#define COORDINATESYSTEM_HPP
#include "MGeomerty/Point.hpp"
#include "MGeomerty/Vector.hpp"
#include <MGeomerty/Geometry.hpp>
#include <cstdint>


class CoordSystem{
    mgm::Rect4u rect_;
    double scaleX_, scaleY_;
    mgm::Vector2f offset_;
public:
    CoordSystem() : rect_({0,0, 100, 100}), scaleX_(1), scaleY_(-1), offset_(0, 0) {}

    CoordSystem(const mgm::Rect4u& rect, const mgm::Point2f& minimal, const mgm::Point2f& maximal):
        rect_(rect), scaleX_(rect.w / (maximal.x - minimal.x)), scaleY_(rect.h / (maximal.y - minimal.y)),
        offset_(-minimal.x, -minimal.y) {}

    mgm::Point2u transform(const mgm::Point2f& point);

    void moveTo(uint32_t x, uint32_t y);
    void resize(uint32_t w, uint32_t h);

    void setFrame(const mgm::Point2f& minimal, const mgm::Point2f& maximal);
};
#endif /* COORDINATESYSTEM_HPP */
