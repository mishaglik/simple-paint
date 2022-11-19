#include "Pen.hpp"

extern "C" void init_module()
{
    addTool(new Grayer);
}

void Grayer::apply(Image* image, const Event* event)
{
    image_ = image;
    if(event->type == EventType::MousePressed) onMousePress   (&event->Oleg.mbedata);
    if(event->type == EventType::MouseReleased) onMouseRelease(&event->Oleg.mbedata);
    if(event->type == EventType::MouseMoved) onMouseMove      (&event->Oleg.motion);
    image = nullptr;
}

void Grayer::onMousePress(const MouseButtonEventData* event)
{
    if(event->button != MouseButton::Left) return;
    isPressed_ = true;
    image_->putPixel(event->x, event->y, APPCONTEXT->fgColor);
    if(event->shift)
    {
        drawLine(image_, prevDrawn_, {event->x, event->y}, APPCONTEXT->fgColor);
    }
    prevDrawn_ = {event->x, event->y};
}

void Grayer::onMouseRelease(const MouseButtonEventData* event)
{
    if(event->button != MouseButton::Left) return;
    isPressed_ = false;
    interp_.reset();
}

void Grayer::onMouseMove(const MotionEventData* event)
{
    if(!isPressed_) return;
    interp_.addPoint({event->x, event->y});
    for(int i = 1; i <= 100; ++i)
    {
        Point pt = interp_.getPoint(i / 100.);
        image_->putPixel(pt.x, pt.y, APPCONTEXT->fgColor);
    }
    prevDrawn_ = {event->x, event->y};
}

void Grayer::buildSetupWidget()
{
    
}
