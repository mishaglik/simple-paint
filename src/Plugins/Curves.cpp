#include "Curves.hpp"
#include "Interpolate.hpp"
#include <cassert>
#include <iostream>

Curve::Curve()
{
}

void Curve::onMouseMove(const MotionEventData* )
{

}         

void Curve::onMousePress(const MouseButtonEventData* e)
{
    if(e->button == MouseButton::Left) transformImage();
}   

void Curve::onMouseRelease(const MouseButtonEventData* )
{

} 

void Curve::buildSetupWidget()
{
    GrainbowCanvas* gr = new GrainbowCanvas({5,5}, {10, 256}, this);
    gr->fillVertical();
    
    gr = new GrainbowCanvas({15, 5 + 256}, {256, 10}, this);
    gr->fillHorizontal();

    canvas_ = new CurveCanvas(15, 5, 256, this);

    Button* bt = createButton(5, 300, 100, 30, "Reset");
    bt->clicked.connect(canvas_, &CurveCanvas::reset);

    Scrollbar* sb = createScrollbar(5, 350, 200, 10, 1000, 500);
    sb->valueChanged.connect(this, &Curve::changeTension);

}

void CurveCanvas::repaint()
{
    clear(BackgroundColor);

    for(int32_t x = 0; x < w_; ++x)             // Border
    {
        putPixel({0, x},   Colors::Black);
        putPixel({x, 0},   Colors::Black);
        putPixel({255, x}, Colors::Black);
        putPixel({x, 255}, Colors::Black);

        for(uint32_t i = 1; i < 8; ++i)
        {
            putPixel(Point(i * w_ / 8, x), 0x565656ff);
            putPixel(Point(x, i * h_ / 8), 0x565656ff);
        }
    }

    kr_.reset();
    uint32_t lastAdded = 0;
    for(uint32_t i = 0; i < NPoints; ++i)
    {
        if(!points_[i].isActive) continue;

        if(kr_.size() == 0)
        {
            kr_.addPoint(Point{} - points_[i].point);
            kr_.addPoint(Point{});
        }

        kr_.addPoint(points_[i].point);
        lastAdded = i;
        for(int32_t dx = -2 ; dx < 3; ++dx)
        {
            for(int32_t dy = -2 ; dy < 3; ++dy)
            {
                putPixel(Point(points_[i].point.x + dx, w_ - (points_[i].point.y + dy)), 0x101010ff);
            }
        }
    }

    if(kr_.size() != 0)
    {
        kr_.addPoint(Point(w_, h_));
        kr_.addPoint(2 * Point(w_, h_) - points_[lastAdded].point);
    }
    else {
        kr_.addPoint({});
        kr_.addPoint({});
        kr_.addPoint(Point(w_, h_));
        kr_.addPoint(Point(w_, h_));
    }

    assert(kr_.size() >= 4);

    for(int i = 501; i < (kr_.size() - 2) * 500; ++i)
    {
        Point pt = kr_.getPoint(i / 500.);
        putPixel(Point(pt.x, w_ - pt.y), 0x151515ff);

        int32_t valX = 100 * pt.x / w_; 
        int32_t valY = 100 * pt.y / h_; 
        if(valX >= 0 && valX <= 100 && valY >= 0 && valY <= 100)
            values_[valX] = valY;
    }
}  

void booba::init_module()
{
    addTool(new Curve);
}

CurveCanvas::CurveCanvas(int32_t x, int32_t y, uint32_t w, BTool* parent)
    : Canvas(x, y, w, w, parent)
{
    reset();
}

void CurveCanvas::onMousePress(const CanvasEventData* e)
{
    Point evPoint(e->x, h_ - e->y);
    for(uint32_t i = 0; i < NPoints; ++i)
    {
        if(!points_[i].isActive)
        {
            points_[i] = {true, evPoint};
            while(i && points_[i].point.x < points_[i - 1].point.x)
            {
                std::swap(points_[i], points_[i-1]);
                i--;
            }
            capturedPoint_ = i;
            break;
        }

        if((points_[i].point - evPoint).len2() < 25)
        {
            capturedPoint_ = i;
            break;
        }
    }

    repaint();
}
void CurveCanvas::onMouseRelease(const CanvasEventData* e)
{
    if(capturedPoint_ == -1) return;
    points_[capturedPoint_].point = Point(e->x, h_ - e->y);
    points_[capturedPoint_].isActive = (capturedPoint_ == 0 || points_[capturedPoint_].point.x >= points_[capturedPoint_ - 1].point.x);
    
    if(!points_[capturedPoint_].isActive)
    {
        while(capturedPoint_ != NPoints - 1 && points_[capturedPoint_ + 1].isActive)
        {
            std::swap(points_[capturedPoint_], points_[capturedPoint_ + 1]);
            capturedPoint_++;
        } 
    }

    capturedPoint_ = -1;
    repaint();
}

void CurveCanvas::onMouseMove(const CanvasEventData* e)   
{
    if(capturedPoint_ == -1) return;
    points_[capturedPoint_].point = Point(e->x, h_ - e->y);
    points_[capturedPoint_].isActive = (capturedPoint_ == 0 || points_[capturedPoint_].point.x >= points_[capturedPoint_ - 1].point.x);
    repaint();
}

void Curve::transformImage()
{
    for(uint32_t y = 0; y < image_->getH(); ++y)
    {
        for(uint32_t x = 0; x < image_->getW(); ++x)
        {
            Color col = image_->getPixel(x, y);
            col.v(canvas_->getValue(col.v()));
            image_->putPixel(x, y, col);
        }
    }
}

void CurveCanvas::reset()
{
    for(size_t i = 0; i < NPoints; ++i)
    {
        points_[i] = {false, {}};
    }
    repaint();
}

void CurveCanvas::setTension(double tension)
{
    kr_.setTension(tension);
    repaint();
}

void Curve::changeTension(int tension)
{
    canvas_->setTension(tension / 1000.);
}

GrainbowCanvas::GrainbowCanvas(Point pt, mgm::Vector2u size, BTool* parent) :
    Canvas(pt.x, pt.y, size.x, size.y, parent)
{
    
}

void GrainbowCanvas::fillHorizontal()
{
    for(int32_t x = 0; x < w_; ++x)
    {
        Color color = Color::fromHSV(0, 1, 100 * x / w_);
        for(int32_t y = 0; y < h_; ++y)
            putPixel({x, y}, color);
    }
}

void GrainbowCanvas::fillVertical()
{
    for(int32_t y = 0; y < h_; ++y)
    {
        Color color = Color::fromHSV(0, 1, 100 - 100 * y / h_);
        for(int32_t x = 0; x < w_; ++x)
            putPixel({x, y}, color);
    }
}