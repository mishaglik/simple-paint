#include "CoordinateSystem.hpp"
#include "MGeomerty/Point.hpp"

mgm::Point2u CoordSystem::transform(const mgm::Point2f &point){
    return {
        static_cast<unsigned>((point.x + offset_.x) * scaleX_) + rect_.x,
        static_cast<unsigned>((point.y + offset_.y) * scaleY_) + rect_.y
    };
}
