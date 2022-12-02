#include "Blur.hpp"
#include <cmath>
#include <iostream>
#include <numbers>
using namespace bp;

void Blur::onMousePress(const bp::MouseButtonEventData* e)
{
    sharpening_ = e->ctrl;
    Pen::onMousePress(e);
} 

void Blur::buildSetupWidget()
{
    Pen::buildSetupWidget();
    Scrollbar* sb = createScrollbar(5, 70, 100, 15, 100, sigma_);
    sb->valueChanged.connect(this, &Blur::setSigma);
    createLabel(110, 67, 50, 21, "Sigma");

    sb = createScrollbar(5, 90, 100, 15, 500, 50);
    sb->valueChanged.connect(this, &Blur::setDegree);
    createLabel(110, 87, 50, 21, "Sharpening degree");

     sb = createScrollbar(5, 110, 100, 15, 1000, treshold_);
    sb->valueChanged.connect(this, &Blur::setDegree);
    createLabel(110, 107, 50, 21, "Treshhold");

}

extern "C" void init_module()
{
    booba::addTool(new Blur);
}

void Blur::applyTool(const Brush::BrushPoint& pt)
{
    if(pixarr_.get(pt.point.x, pt.point.y)) return;
    pixarr_.set(pt.point.x, pt.point.y);

    // std::cerr << "Overrided\n";

    double rAvg = 0, gAvg = 0, bAvg = 0, summ =0;

    for(int dx = -gSize_; dx <= gSize_; ++dx)
    {
        for(int dy = -gSize_; dy <= gSize_; ++dy)
        {
            Point point = {pt.point.x + dx, pt.point.y + dy};
            if(!isOnImage(image_, point)) point = pt.point;

            Color col = image_->getPixel(point.x, point.y);
            rAvg += gayss_[dx < 0 ? -dx : dx][dy < 0 ? -dy : dy] * col.rf();
            gAvg += gayss_[dx < 0 ? -dx : dx][dy < 0 ? -dy : dy] * col.gf();
            bAvg += gayss_[dx < 0 ? -dx : dx][dy < 0 ? -dy : dy] * col.bf();
            summ += gayss_[dx < 0 ? -dx : dx][dy < 0 ? -dy : dy];
            // std::cerr << dx << " " << dy << gayss_[abs(dx)][abs(dy)] << '\n';
        }
    }

    // rAvg /= summ;
    // bAvg /= summ;
    // gAvg /= summ;

    Color colorAvg = image_->getPixel(pt.point.x, pt.point.y);
    if(!sharpening_)
    {
        colorAvg.rf(rAvg);
        colorAvg.gf(gAvg);
        colorAvg.bf(bAvg);
        // image_->putPixel(pt.point.x, pt.point.y, 0);
    }
    else {
        if(fabs(colorAvg.gf() - gAvg) > treshold_ / 1000.)
        {
            colorAvg.rf(std::max(0.,std::min(1., (colorAvg.rf() - rAvg) * degee_ / 10. + rAvg)));
            colorAvg.gf(std::max(0.,std::min(1., (colorAvg.gf() - gAvg) * degee_ / 10. + gAvg)));
            colorAvg.bf(std::max(0.,std::min(1., (colorAvg.bf() - bAvg) * degee_ / 10. + bAvg)));
        }
    }
    apply_.push_back({pt.point, colorAvg}); 
}

void Blur::brushDraw(const Point& pt)
{
    apply_.clear();
    Pen::brushDraw(pt);

    for(auto [point, col] : apply_)
    {
        image_->putPixel(point.x, point.y, col);
    }
}


void Blur::fillGayss()
{
    double sigma = sigma_ / 10.;
    gSize_ = SIGMA_LIMIT * sigma / 10;
    gSize_ = std::min(gSize_, 20);
    gayss_.resize(gSize_ + 1);
    for(size_t x = 0; x <= gSize_; ++x)
    {
        gayss_[x].resize(gSize_ + 1);
        for(size_t y = 0; y <= gSize_; ++y)
        {
            gayss_[x][y] = std::exp(-static_cast<double>(x*x + y*y) / (2 * sigma * sigma)) / (2 * std::numbers::pi * sigma * sigma);
            // std::cerr << x << " " << y << " " << gayss_[x][y] << '\n';
        }
    }
}

void Blur::setSigma(int sigma)
{
    sigma_ = sigma;
    fillGayss();    
}
