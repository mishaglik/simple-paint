#include "Pippet.hpp"

static bool isOnImage(Image* image, int x, int y)
{
    return x >= 0 && x < static_cast<int>(image->getW()) && 
           y >= 0 && y < static_cast<int>(image->getH());
}

void Pippet::apply(Image* image, const Event* event)
{
    if(event->type == EventType::MousePressed && event->Oleg.mbedata.button == MouseButton::Left && isOnImage(image, event->Oleg.mbedata.x, event->Oleg.mbedata.y))
    {
        (event->Oleg.mbedata.ctrl ? APPCONTEXT->bgColor : APPCONTEXT->fgColor) = image->getPixel(event->Oleg.mbedata.x, event->Oleg.mbedata.y);
    }
}

static const GUID GUID_ = {"dbc917bf-0831-4dab-814e-586bf7bea4f3"};

extern "C" GUID getGUID()
{
    return GUID_;
}

extern "C" void init_module()
{
    addTool(new Pippet);
}
