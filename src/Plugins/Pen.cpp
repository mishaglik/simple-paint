#include "Pen.hpp"
#include "BrezLine.hpp"
#include "BBrushes.hpp"
#include <iostream>
using namespace bp;

bool bp::isOnImage(Image* image, const Point& pt)
{
    return pt.x >= 0 && pt.x < static_cast<int64_t>(image->getW()) && 
           pt.y >= 0 && pt.y < static_cast<int64_t>(image->getH());
}

Pen::Pen() : pixarr_(0, 0)
{
    // brush_ = new Brushes::CircleBrush(settts_);
    Brush* (*getBr)();
    Brush::BrushSettings* (*getBrSetts)();
    getBr = reinterpret_cast<Brush* (*)()>(booba::getLibSymbol({BRUSHES_GUID}, "getCurrentBrush")); 
    getBrSetts = reinterpret_cast<Brush::BrushSettings* (*)()>(booba::getLibSymbol({BRUSHES_GUID}, "getCurrentBrushSettings")); 
    if(getBr == nullptr ||getBrSetts == nullptr)
    {
        std::cerr << "Not found getCurrentBrush \n";
    }
    brush_ = getBr();
    settts_ = getBrSetts();
}


void Pen::onMousePress  (const MouseButtonEventData* event)
{
    if(image_->getH() != pixarr_.getH() || image_->getW() != pixarr_.getW())
        usedReset();
    Point evPoint(event->x, event->y);
    if(event->button == MouseButton::Left && isOnImage(image_, evPoint))
    {
        pressed_ = true;
        if(event->shift)
        {
            for(Point pt : BrezLine(prevDrawn_, evPoint))
            {
                if(100 * (prevDrawn_ - pt).len2() > interval * interval)
                {
                    brushDraw(pt);
                }
            }
        }

        brushDraw(evPoint);
    }
}

void Pen::onMouseRelease(const MouseButtonEventData* event)
{
    if(event->button == MouseButton::Left)
    {
        pressed_ = false;
        usedReset();
    }
}

void Pen::onMouseMove(const MotionEventData* event)
{
    if(image_->getH() != pixarr_.getH() || image_->getW() != pixarr_.getW())
        usedReset();
    Point ePoint(event->x, event->y);
    if(pressed_ && isOnImage(image_, ePoint))
    {
        for(Point pt : BrezLine(prevDrawn_, ePoint))
        {
            if((prevDrawn_ - pt).len2() > interval * interval)
            {
                brushDraw(pt);
            }
        }
    }
}

void Pen::brushDraw(const Point& pt)
{
    prevDrawn_ = pt;

    for(auto point : brush_->at(pt))
    {
        if(isOnImage(image_, point.point))
            applyTool(point);
    }
}

void Pen::applyTool(const Brush::BrushPoint& pt)
{
    // if(pixarr_.get(pt.point.x, pt.point.y)) return;
    // pixarr_.set(pt.point.x, pt.point.y);

    Color imgColor = image_->getPixel(pt.point.x, pt.point.y);
    Color color = APPCONTEXT->fgColor;
    color.a(pt.opacity);
    imgColor.ablend(color);
    image_->setPixel(pt.point.x, pt.point.y, imgColor);
}


void Pen::usedReset()
{
    if(image_->getH() != pixarr_.getH() || image_->getW() != pixarr_.getW())
    {
        pixarr_.resize(image_->getW(), image_->getH());
    }
    else {
        pixarr_.clear();
    }
}

void Pen::buildSetupWidget()
{
    Scrollbar* sb = nullptr;
    setToolBarSize(300, 400);

    sb = createScrollbar(5, 10, 100, 15, 200, 10);
    createLabel(110, 7, 50, 21, "Size");
    sb->valueChanged.connect(this, &Pen::setBrushSize);

    sb = createScrollbar(5, 30, 100, 15, 255, 10);
    createLabel(110, 27, 50, 21, "Opacity");
    sb->valueChanged.connect(this, &Pen::setOpacity);

    sb = createScrollbar(5, 50, 100, 15, 200, 10);
    createLabel(110, 47, 50, 21, "Interval");
    sb->valueChanged.connect(this, &Pen::setInterval);
}
