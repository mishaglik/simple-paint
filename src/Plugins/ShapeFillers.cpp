#include "ShapeFillers.hpp"
#include <utility>
#include <iostream>
extern "C" void init_module()
{
    addTool(new RectFiller{});
    addTool(new EllipseFiller{});
}

void RectFiller::apply(Image* image, const Event* event)
{
    if(event->type == booba::EventType::MousePressed && event->Oleg.mbedata.button == MouseButton::Left)
    {
        if(keepPoint)
        {
            keepPoint = false;
            int32_t curX = event->Oleg.mbedata.x;
            int32_t curY = event->Oleg.mbedata.y;
            if(curX > prevX_) std::swap(curX, prevX_);
            if(curY > prevY_) std::swap(curY, prevY_);
            int32_t color = (event->Oleg.mbedata.ctrl ? APPCONTEXT->bgColor : APPCONTEXT->fgColor);

            for(int32_t x = curX; x < prevX_; ++x)
            {
                for(int32_t y = curY; y < prevY_; ++y)
                {
                    image->putPixel(x, y, color);
                }
            }
        }
        else
        {
            keepPoint = true;
            prevX_ = event->Oleg.mbedata.x;
            prevY_ = event->Oleg.mbedata.y;
        }
    }
}

void EllipseFiller::apply(Image* image, const Event* event)
{
    if(event->type == booba::EventType::MousePressed && event->Oleg.mbedata.button == MouseButton::Left)
    {
        if(keepPoint)
        {
            keepPoint = false;
            int32_t curX = event->Oleg.mbedata.x;
            int32_t curY = event->Oleg.mbedata.y;
            if(curX > prevX_) std::swap(curX, prevX_);
            if(curY > prevY_) std::swap(curY, prevY_);
            int32_t w = (prevX_ - curX) / 2;
            int32_t h = (prevY_ - curY) / 2;
            
            if(event->Oleg.mbedata.shift)
            {
                w *= 2;
                h *= 2;
            }
            
            int32_t w2 = w * w;
            int32_t h2 = h * h;
            // std::cerr << "Rect: " << curX << " " << curY << " " << prevX_ << " " << prevY_ << "\n";
            int32_t color = (event->Oleg.mbedata.ctrl ? APPCONTEXT->bgColor : APPCONTEXT->fgColor);

            for(int32_t x = curX; x < prevX_; ++x)
            {
                for(int32_t y = curY; y < prevY_; ++y)
                {
                    int32_t dx2 = (x - curX - w) * (x - curX - w);
                    int32_t dy2 = (y - curY - h) * (y - curY - h);
                    if(dx2 * h2 + dy2 * w2 <= w2 * h2)
                        image->putPixel(x, y, color);
                }
            }
        }
        else
        {
            keepPoint = true;
            prevX_ = event->Oleg.mbedata.x;
            prevY_ = event->Oleg.mbedata.y;
        }
    }
}
