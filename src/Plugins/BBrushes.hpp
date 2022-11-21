#ifndef PLUGINS_BBRUSHES_HPP
#define PLUGINS_BBRUSHES_HPP

#include "Brushes.hpp"

namespace Brushes {

    class PointBrush : public Brush
    {
    public:
        PointBrush(const BrushSettings& settings) : Brush(settings) {}
        
        virtual void setCenter(const Point& center) override { bpt_ = {center, settings_.opacity}; }
        virtual bool nextPoint() override { return true; }
    };

    class CircleBrush : public Brush
    {
        Point center_;
        int32_t radius_;
    public:
        CircleBrush(const BrushSettings& settings) : Brush(settings) {}
        
        virtual void setCenter(const Point& center) override;
        virtual bool nextPoint() override;
    };
}

#endif /* PLUGINS_BBRUSHES_HPP */
