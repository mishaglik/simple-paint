#include "Curves.hpp"
#include "Interpolate.hpp"
#include <iostream>

Curve::Curve()
{
    for(int i = 0; i < NPoints; ++i)
        points_[i] = Point(i * 255 / (NPoints - 1), i * 255 / (NPoints - 1));
}

void Curve::reset()
{
    for(int i = 0; i < NPoints; ++i)
        points_[i] = Point(i * 255 / (NPoints - 1), i * 255 / (NPoints - 1));
    canvas_->repaint();
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
    canvas_ = new CurveCanvas(createCanvas(5, 5, 256, 256), 256, 256, this);
    canvases_.push_back(canvas_);

    Button* bt = createButton(5, 300, 100, 30, "Reset");
    bt->clicked.connect(this, &Curve::reset);
}

void CurveCanvas::repaint()
{
    for(int32_t x = 0; x < w_; ++x)
        for(int32_t y = 0; y < h_; ++y)
            putPixel({x, y}, 0x393939ff);
    
    // std::cerr << "Pixe pul\n";

    for(int32_t x = 0; x < w_; ++x)
    {
        putPixel({0, x}, 0xff);
        putPixel({x, 0}, 0xff);
        putPixel({255, x}, 0xff);
        putPixel({x, 255}, 0xff);
    }

    KatmulRom kr;
    kr.addPoint(parent_->points_[0]);    
    kr.addPoint(parent_->points_[0]);    


    for(uint32_t i = 0; i < parent_->NPoints; ++i)
    {
        if(parent_->points_[i].x == parent_->points_[i].y) continue;
        kr.addPoint(parent_->points_[i]);
        if(kr.points_ == 3) continue;
        for(int i = 0; i <= 1000; ++i)
        {
            Point pt = kr.getPoint(i / 1000.);
            putPixel({pt.x, 256 - pt.y}, 0xff);
        }
        // int val = parent_->getNewValue(i);
        // std::cerr << i << ' ' << val << '\n';
    } 
    kr.addPoint(parent_->points_[parent_->NPoints - 1]);
    for(int i = 0; i <= 1000; ++i)
    {
        Point pt = kr.getPoint(i / 1000.);
        putPixel({pt.x, 256 - pt.y}, 0xff);
    }

    kr.addPoint(parent_->points_[parent_->NPoints - 1]);
    for(int i = 0; i <= 1000; ++i)
    {
        Point pt = kr.getPoint(i / 1000.);
        putPixel({pt.x, 256 - pt.y}, 0xff);
    }

}  

uint8_t Curve::getNewValue(uint8_t value)
{

    KatmulRom kr;
    kr.addPoint(points_[0]);    
    kr.addPoint(points_[0]);    

    Point pointL = points_[0], pointR = points_[0];

    for(uint32_t i = 0; i < NPoints; ++i)
    {
        if(points_[i].x == points_[i].y) continue;
        kr.addPoint(points_[i]);
        if(kr.points_ != 3)
        {
            if(pointL.x <= value && pointR.x >= value)
            {
                return kr.getPoint((value - pointL.x) /static_cast<double>(pointR.x - pointL.x)).y;
            }
        }
        pointL = pointR;
        pointR = points_[i];
        // int val = parent_->getNewValue(i);
        // std::cerr << i << ' ' << val << '\n';
    } 
    for(int _ = 0; _ < 2; ++_)
    {

        kr.addPoint(points_[NPoints - 1]);
        if(pointL.x <= value && pointR.x >= value)
        {
            return kr.getPoint((value - pointL.x) /static_cast<double>(pointR.x - pointL.x)).y;
        }
        pointL = pointR;
        pointR = points_[NPoints - 1];
    }
    return 0;
    uint32_t pt1 = getLowerB({value, 0});
    uint32_t pt2 = getUpperB({value, 0});

    // std::cerr << "Less: " << (int)value << " " << less << '\n';
    // if(pt1 == NPoints-1)
    // {
    //     return 255;
    // }

    // if(pt1 == 0)
    // {
    //     return points_[1].y * value / points_[1].x;
    // }

    // uint32_t pt0 = getLowerB({points_[pt1].x - 1, 0});

    // if(pt2 == NPoints - 1)
    // {
    //     return points_[NPoints - 2].y + (255 - points_[NPoints - 2].y) * (value - points_[NPoints - 2].x) / (255 - points_[NPoints - 2].x);
    // }

    // uint32_t pt3 = getUpperB({points_[pt2].x, 0});

    // KatmulRom kr;
    // kr.addPoint(points_[pt0]);
    // kr.addPoint(points_[pt1]);
    // kr.addPoint(points_[pt2]);
    // kr.addPoint(points_[pt3]);

    // Point pt = kr.getPoint((value - points_[pt1].x) / static_cast<double>(points_[pt2].x - points_[pt1].y));
    // return pt.y;
}


uint32_t Curve::getLowerB(Point pt)
{
    // uint32_t left = 0, right = NPoints;
    // while (right - left > 1) {
    //     uint32_t middle = (left + right) / 2;
    //     (points_[left].x <= pt.x ? left : right) = middle;
    // }
    uint32_t left = 0;
    for(uint32_t i = 0; i < NPoints; ++i)
        if(points_[i].x <= pt.x && points_[i].x != points_[i].y) left = i;
    return left;
}

uint32_t Curve::getUpperB(Point pt)
{
    // uint32_t left = 0, right = NPoints;
    // while (right - left > 1) {
    //     uint32_t middle = (left + right) / 2;
    //     (points_[left].x <= pt.x ? left : right) = middle;
    // }
    uint32_t left = 0;
    for(uint32_t i = 0; i < NPoints; ++i)
        if(points_[i].x > pt.x && points_[i].x != points_[i].y) return i;
    return NPoints - 1;
}
void booba::init_module()
{
    addTool(new Curve);
}

CurveCanvas::CurveCanvas(uint64_t id,  uint32_t w, uint32_t h, Curve* parent)
    : Canvas(id, w, h), parent_(parent)
{
    repaint();
}

void CurveCanvas::onMousePress(const CanvasEventData* e)
{
    // uint32_t pt = parent_->getLowerB({e->x, e->y});
    uint32_t pt = 1;
    for(uint32_t i = 1; i < parent_->NPoints-1; ++i)
    {
        if(parent_->points_[i].x < e->x) pt = i;
    }

    parent_->points_[pt] = {e->x, 255 - e->y};
    repaint();
    // std::cerr << "Moved " << pt << '\n';
}

void Curve::transformImage()
{
    for(uint32_t y = 0; y < image_->getH(); ++y)
    {
        for(uint32_t x = 0; x < image_->getW(); ++x)
        {
            Color col = image_->getPixel(x, y);
            uint8_t newval = getNewValue(255 * col.v() / 100);
            col.v(100 * newval / 255);
            image_->putPixel(x, y, col);
        }
    }
}
