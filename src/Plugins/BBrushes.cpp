#include "BBrushes.hpp"
#include <iostream>

namespace Brushes {
    void CircleBrush::setCenter(const Point& center)
    {
        center_ = center;
        radius_ = settings_.size / 2;

        bpt_ = {center, settings_.opacity};
        bpt_.point -= Point(0, radius_);
    }

    bool CircleBrush::nextPoint()
    {
        if(bpt_.point.y >= center_.y + radius_) return true;

        bpt_.point.x++;
        
        int32_t dx2 = (bpt_.point.x - center_.x) * (bpt_.point.x - center_.x);
        int32_t dy2 = (bpt_.point.y - center_.y) * (bpt_.point.y - center_.y);
        
        if(dx2 + dy2 > radius_ * radius_)
        {
            bpt_.point.y++;
            dy2 = (bpt_.point.y - center_.y) * (bpt_.point.y - center_.y);

            bpt_.point.x = center_.x - static_cast<int>(std::sqrt(radius_ * radius_ - dy2));
        }
        // std::cerr << "+x\n";
        return false;
    }

}
