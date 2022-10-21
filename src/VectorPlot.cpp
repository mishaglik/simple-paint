#include "VectorPlot.hpp"
#include "AbstractGL/AWindow.hpp"
#include "Widgets/Widget.hpp"
#include "CoordinateSystem.hpp"
#include "MGeomerty/Point.hpp"
#include "MGeomerty/Vector.hpp"
#include <iostream>

VectorPlot::VectorPlot(uint32_t x, uint32_t y, uint32_t w, uint32_t h, double minX, double minY, double maxX, double maxY, aGL::Widget* parent):
    aGL::Widget({x,y,w,h}, parent), CoordSystem({0, 0, w, h}, {minX, minY}, {maxX, maxY}), vec_(1, 1)
{

}

void VectorPlot::drawForeground() const 
{
    mgm::Point2f finPoint = startPoint_;
    mgm::Vector2f vec = rotate(vec_, angle_);

    finPoint += vec;

    surface->drawLine(transform(startPoint_), transform(finPoint), aGL::Colors::Red);

    mgm::Point2f pt = finPoint;

    mgm::Vector2f shift = vec;
    shift *= -0.1;
    pt += shift;
    
    mgm::Vector2f orth = mgm::getOrthogonal(vec);
    orth *= 0.05;
    pt += orth;

    surface->drawLine(transform(finPoint), transform(pt) ,0xFF0000FF);
    orth *= -2;
    pt += orth;

    surface->drawLine(transform(finPoint), transform(pt) ,0xFF0000FF);

}

void VectorPlot::drawBackground() const 
{
    if(skinned())
    {
        surface->clear(aGL::Colors::White);
    
        aGL::Sprite sp = sm_->getTexture(texId_);
        aGL::Rect rect = sp.getTextureRect();
        sp.setRotation(-angle_);
        surface->drawSprite(aGL::Point(
            -(static_cast<int>(rect.w) - static_cast<int>(aGL::Widget::rect_.w)) / 2,
            -(static_cast<int>(rect.h) - static_cast<int>(aGL::Widget::rect_.h)) / 2
        ), sp);
    }
    else surface->clear(aGL::Colors::White);
}

aGL::EventHandlerState VectorPlot::onPaintEvent(const aGL::Event*)
{
    drawBackground();
    drawForeground();
    return aGL::EventHandlerState::Accepted;
}


void VectorPlot::setVector(const mgm::Vector2f& vec)
{
    vec_ = vec;
}

const mgm::Vector2f& VectorPlot::getVector() const 
{
    return vec_;
}

mgm::Vector2f& VectorPlot::getVectorRef(){
    return vec_;
}

VectorPlot::~VectorPlot(){

}

void VectorPlot::setAngle(double a){
    angle_ = a;
}

void VectorPlot::addAngle(double a){
    angle_ += a;
}

aGL::EventHandlerState VectorPlot::onMouseMoveEvent (const aGL::Event* event)
{
    mAssert(event->type == aGL::EventType::MouseMoved);
    if(!captured || !mgm::contains(aGL::Widget::rect_, event->mmed.point)) return aGL::EventHandlerState::Dropped;
    vec_ = rTransform(event->mmed.point) - startPoint_;
    return aGL::EventHandlerState::Accepted;
}

aGL::EventHandlerState VectorPlot::onMouseButtonPressEvent(const aGL::Event* event)
{
    if(event->mbed.button == aGL::MouseButton::Left && mgm::contains(aGL::Widget::rect_, event->mbed.point)){
        aGL::Point pt = event->mbed.point;
        vec_ = rTransform(pt) - startPoint_;
        angle_ = 0;
        captured = true;
        return aGL::EventHandlerState::Accepted;
    }
    return aGL::Widget::onMouseButtonReleaseEvent(event);
}

aGL::EventHandlerState VectorPlot::onMouseButtonReleaseEvent(const aGL::Event* event)
{
    if(event->mbed.button == aGL::MouseButton::Left)
    {
        captured = false;
        return aGL::EventHandlerState::Accepted;
    }
    return aGL::Widget::onMouseButtonReleaseEvent(event);
}


void VectorPlot::update(){
    if(!captured) addAngle(speed_);
}

void VectorPlot::setSpeed(double speed){
    speed_ = speed;
}
