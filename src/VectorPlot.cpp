#include "VectorPlot.hpp"
#include "AbstractGL/AWindow.hpp"
#include "AbstractGL/Widget.hpp"
#include "CoordinateSystem.hpp"
#include "MGeomerty/Point.hpp"
#include "MGeomerty/Vector.hpp"

VectorPlot::VectorPlot(uint32_t x, uint32_t y, uint32_t w, uint32_t h, double minX, double minY, double maxX, double maxY):
    aGL::Widget({x,y,w,h}), CoordSystem(aGL::Widget::rect_, {minX, minY}, {maxX, maxY}), vec_(1, 1)
{

}

void VectorPlot::drawForeground(const aGL::Window* window){
    mgm::Point2f finPoint = startPoint_;
    finPoint += vec_;
    
    window->drawLine(transform(startPoint_), transform(finPoint) ,0xFF0000FF);

    mgm::Point2f pt = finPoint;

    mgm::Vector2f shift = vec_;
    shift *= -0.1;
    pt += shift;
    
    mgm::Vector2f orth = mgm::getOrthogonal(vec_);
    orth *= 0.05;
    pt += orth;

    window->drawLine(transform(finPoint), transform(pt) ,0xFF0000FF);
    orth *= -2;
    pt += orth;

    window->drawLine(transform(finPoint), transform(pt) ,0xFF0000FF);

}

void VectorPlot::drawBackground(const aGL::Window* window){
    window->drawRect(getRect(), aGL::Colors::White);
}

void VectorPlot::render(const aGL::Window& window){
    drawBackground(&window);
    drawForeground(&window);
}


void VectorPlot::setVector(const mgm::Vector2f& vec){
    vec_ = vec;
}

const mgm::Vector2f& VectorPlot::getVector() const {
    return vec_;
}

mgm::Vector2f& VectorPlot::getVectorRef(){
    return vec_;
}

VectorPlot::~VectorPlot(){

}
