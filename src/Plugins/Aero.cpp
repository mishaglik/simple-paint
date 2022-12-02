#include "Pen.hpp"
#include "Aero.hpp"
#include "BBrushes.hpp"
#include <iostream>
#include "BrezLine.hpp"

extern const GUID bp::GUID_ = {"61d373f9-ac57-44a2-b38d-1d2ece00c6d0"};

extern "C" void init_module()
{
    addTool(new Aero);
    addTool(new Pen);
}

Aero::Aero()
{
    brush = new Brushes::CircleBrush(settts_);
}


void Aero::onMousePress(const MouseButtonEventData* event)
{
    if(event->button != MouseButton::Left) return;
    Point evPoint(event->x, event->y);
    if(!isOnImage(image_, evPoint)) return;

    pressed_ = true;
    

    brushDraw(evPoint);
    if(event->shift)
    {
        for(const Point& pt : BrezLine(prevDrawn_, evPoint))
        {
            brushDraw(pt);
        }
        // drawLine(image_, prevDrawn_, evPoint, APPCONTEXT->fgColor);
    }
    prevDrawn_ = evPoint;
}

void Aero::onMouseRelease(const MouseButtonEventData* event)
{
    if(event->button != MouseButton::Left) return;
    Point evPoint(event->x, event->y);

    if(!isOnImage(image_, evPoint)) return;
    interp_.reset();
}

void Aero::onMouseMove(const MotionEventData* event)
{
    if(!pressed_) return;
    Point evPoint(event->x, event->y);

    if(!isOnImage(image_, evPoint)) return;

    interp_.addPoint(evPoint);
    uint32_t dist = (Point(event->x, event->y) -= prevDrawn_).len2();
    dist /= (settts_.size) * (settts_.size);
    dist = std::max(dist, 1u);
    const int multiplier = 4;
    for(uint32_t i = 1; i <= multiplier * prevLen_; ++i)
    {
        Point pt = interp_.getPoint(i / static_cast<double>(multiplier * prevLen_));
        brushDraw(pt);
    }
    prevLen_ = dist;
    prevDrawn_ = evPoint;
}

void Aero::buildSetupWidget()
{
    createLabel(110, 7 , 50, 21, "Size");
    createLabel(110, 27, 50, 21, "Opacity");
    createLabel(110, 47, 50, 21, "Density");
    Scrollbar* sb = createScrollbar(5, 10, 100, 15, 500, 5);
    sb->valueChanged.connect(this, &Aero::setBrushSize);

    sb = createScrollbar(5, 30, 100, 15, 200, 5);
    sb->valueChanged.connect(this, &Aero::setOpacity);

    sb = createScrollbar(5, 50, 100, 15, 100, 5);
    sb->valueChanged.connect(this, &Aero::setDensity);
}

void Aero::brushDraw(const Point& pt)
{
    for(const Brush::BrushPoint& point : brush->at(pt))
    {
        if(!isOnImage(image_, point.point)) continue;
        if((rand() % 100) >= density_) continue;
        Color color = APPCONTEXT->fgColor;
        color.a(point.opacity);

        Color curColor = image_->getPixel(point.point.x, point.point.y);
        curColor.ablend(color);
        
        image_->setPixel(point.point.x, point.point.y, curColor);
        
        // std::cerr << point.point.x << " " <<  point.point.y << '\n';
    }
}
