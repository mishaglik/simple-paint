#include "Pen.hpp"
#include "BBrushes.hpp"
#include <iostream>

extern "C" void init_module()
{
    addTool(new Pen);
}

Pen::Pen()
{
    brush = new Brushes::CircleBrush(settts_);
}


static bool isOnImage(Image* image, const Point& pt)
{
    return pt.x >= 0 && pt.x < static_cast<int>(image->getW()) && 
           pt.y >= 0 && pt.y < static_cast<int>(image->getH());
}

void Pen::apply(Image* image, const Event* event)
{
    image_ = image;
    if(event->type == EventType::MousePressed) onMousePress   (&event->Oleg.mbedata);
    if(event->type == EventType::MouseReleased) onMouseRelease(&event->Oleg.mbedata);
    if(event->type == EventType::MouseMoved) onMouseMove      (&event->Oleg.motion);
    if(event->type == EventType::ScrollbarMoved) settts_.size = event->Oleg.smedata.value;
    image = nullptr;
}

void Pen::onMousePress(const MouseButtonEventData* event)
{
    if(event->button != MouseButton::Left) return;
    if(!isOnImage(image_, {event->x, event->y})) return;

    isPressed_ = true;
    // image_->putPixel(event->x, event->y, APPCONTEXT->fgColor);
    brushDraw({event->x, event->y});
    if(event->shift)
    {
        drawLine(image_, prevDrawn_, {event->x, event->y}, APPCONTEXT->fgColor);
    }
    prevDrawn_ = {event->x, event->y};
}

void Pen::onMouseRelease(const MouseButtonEventData* event)
{
    if(event->button != MouseButton::Left) return;
    if(!isOnImage(image_, {event->x, event->y})) return;

    isPressed_ = false;
    interp_.reset();
}

void Pen::onMouseMove(const MotionEventData* event)
{
    if(!isPressed_) return;
    if(!isOnImage(image_, {event->x, event->y})) return;

    interp_.addPoint({event->x, event->y});
    uint32_t dist = (Point{event->x, event->y} -= prevDrawn_).len2();
    // dist /= (settts_.size) * (settts_.size);
    dist = std::max(dist, 1u);
    for(uint32_t i = 1; i*i <= 4 * dist; ++i)
    {
        Point pt = interp_.getPoint(i / static_cast<double>(4 * dist));
        // image_->putPixel(pt.x, pt.y, APPCONTEXT->fgColor);
        brushDraw(pt);
    }
    prevDrawn_ = {event->x, event->y};
}

void Pen::buildSetupWidget()
{
    createScrollbar(0, 0, 100, 10, 100, 5);
}

void Pen::brushDraw(const Point& pt)
{
    for(const Brush::BrushPoint& point : brush->at(pt))
    {
        if(!isOnImage(image_, point.point)) continue;
        Color color = APPCONTEXT->fgColor;
        color.a(point.opacity);

        Color curColor = image_->getPixel(point.point.x, point.point.y);
        curColor.ablend(color);
        
        image_->putPixel(point.point.x, point.point.y, curColor);
        
        // std::cerr << point.point.x << " " <<  point.point.y << '\n';
    }
}
