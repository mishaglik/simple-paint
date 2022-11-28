#include "Pen.hpp"
#include "Aero.hpp"
#include "BBrushes.hpp"
#include <iostream>
#include "BrezLine.hpp"

extern "C" void init_module()
{
    addTool(new Aero);
    addTool(new Pen);
}

Aero::Aero()
{
    brush = new Brushes::CircleBrush(settts_);
}

// void Aero::apply(Image* image, const Event* event)
// {
//     image_ = image;
//     if(event->type == EventType::MousePressed) onMousePress   (&event->Oleg.mbedata);
//     if(event->type == EventType::MouseReleased) onMouseRelease(&event->Oleg.mbedata);
//     if(event->type == EventType::MouseMoved) onMouseMove      (&event->Oleg.motion);
//     if(event->type == EventType::ScrollbarMoved) settts_.size = event->Oleg.smedata.value + 1;
//     image = nullptr;
// }

void Aero::onMousePress(const MouseButtonEventData* event)
{
    if(event->button != MouseButton::Left) return;
    if(!isOnImage(image_, {event->x, event->y})) return;

    pressed_ = true;
    

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
    interp_.reset();
}

void Aero::onMouseMove(const MotionEventData* event)
{
    if(!pressed_) return;
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
    createLabel(110, -10, 100, 20, "Size");
    createLabel(110, 15, 100, 20, "Opacity");
    createLabel(110, 30, 100, 20, "Density");
    Scrollbar* sb = createScrollbar(5, 0, 100, 10, 500, 5);
    sb->valueChanged.connect(this, &Aero::setBrushSize);

    sb = createScrollbar(5, 20, 100, 10, 200, 5);
    sb->valueChanged.connect(this, &Aero::setOpacity);

    sb = createScrollbar(5, 40, 100, 10, 100, 5);
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
        
        image_->putPixel(point.point.x, point.point.y, curColor);
        
        // std::cerr << point.point.x << " " <<  point.point.y << '\n';
    }
}
