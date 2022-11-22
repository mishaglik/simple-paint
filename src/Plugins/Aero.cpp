#include "Aero.hpp"
#include "BBrushes.hpp"
#include <iostream>
#include "BrezLine.hpp"

extern "C" void init_module()
{
    addTool(new Aero);
}

Aero::Aero()
{
    brush = new Brushes::CircleBrush(settts_);
}


static bool isOnImage(Image* image, const Point& pt)
{
    return pt.x >= 0 && pt.x < static_cast<int>(image->getW()) && 
           pt.y >= 0 && pt.y < static_cast<int>(image->getH());
}

void Aero::apply(Image* image, const Event* event)
{
    image_ = image;
    if(event->type == EventType::MousePressed) onMousePress   (&event->Oleg.mbedata);
    if(event->type == EventType::MouseReleased) onMouseRelease(&event->Oleg.mbedata);
    if(event->type == EventType::MouseMoved) onMouseMove      (&event->Oleg.motion);
    if(event->type == EventType::ScrollbarMoved) settts_.size = event->Oleg.smedata.value + 1;
    image = nullptr;
}

void Aero::onMousePress(const MouseButtonEventData* event)
{
    if(event->button != MouseButton::Left) return;
    if(!isOnImage(image_, {event->x, event->y})) return;

    isPressed_ = true;
    

    brushDraw({event->x, event->y});
    if(event->shift)
    {
        for(const Point& pt : BrezLine(prevDrawn_, {event->x, event->y}))
        {
            brushDraw(pt);
        }
        // drawLine(image_, prevDrawn_, {event->x, event->y}, APPCONTEXT->fgColor);
    }
    prevDrawn_ = {event->x, event->y};
}

void Aero::onMouseRelease(const MouseButtonEventData* event)
{
    if(event->button != MouseButton::Left) return;
    if(!isOnImage(image_, {event->x, event->y})) return;

    isPressed_ = false;
    interp_.reset();
}

void Aero::onMouseMove(const MotionEventData* event)
{
    if(!isPressed_) return;
    if(!isOnImage(image_, {event->x, event->y})) return;

    interp_.addPoint({event->x, event->y});
    uint32_t dist = (Point{event->x, event->y} -= prevDrawn_).len2();
    dist /= (settts_.size) * (settts_.size);
    dist = std::max(dist, 1u);
    const int multiplier = 4;
    for(uint32_t i = 1; i <= multiplier * prevLen_; ++i)
    {
        Point pt = interp_.getPoint(i / static_cast<double>(multiplier * prevLen_));
        brushDraw(pt);
    }
    prevLen_ = dist;
    prevDrawn_ = {event->x, event->y};
}

void Aero::buildSetupWidget()
{
    createScrollbar(0, 0, 100, 10, 500, 5);
}

void Aero::brushDraw(const Point& pt)
{
    for(const Brush::BrushPoint& point : brush->at(pt))
    {
        if(!isOnImage(image_, point.point)) continue;
        if((rand() & 15)) continue;
        Color color = APPCONTEXT->fgColor;
        color.a(point.opacity);

        Color curColor = image_->getPixel(point.point.x, point.point.y);
        curColor.ablend(color);
        
        image_->putPixel(point.point.x, point.point.y, curColor);
        
        // std::cerr << point.point.x << " " <<  point.point.y << '\n';
    }
}
