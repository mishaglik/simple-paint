#include "Raytracer.hpp"
#include "RenderSphere.hpp"
#include "RenderPlane.hpp"
#include <iostream>
#include "ColorAvg.hpp"

Raytracer::Raytracer(uint32_t x, uint32_t y, uint32_t w, uint32_t h) : aGL::Widget({x, y, w, h}), camera_({0, 0, -1000})
{
    
    objlist_.push_back(new RTObjs::RenderPlane ({   0,     1,   0.05}, {0, 150,0}, false,  0x00a520ff));
    objlist_.push_back(new RTObjs::RenderSphere({   0,     20, 1000}, 100, false, aGL::Colors::Magenta));
    objlist_.push_back(new RTObjs::RenderSphere({ 300,     -20, 1000}, 100, false, aGL::Colors::LGray));
    objlist_.push_back(new RTObjs::RenderSphere({   0,  -1e5, 1000}, 5e4, true,  aGL::Colors::White));
    objlist_.push_back(new RTObjs::RenderSphere({ 155,  -300, 1000},  40, true,  aGL::Colors::Yellow));
    // objlist_.push_back(new RTObjs::RenderPlane ({   0,     1,   1}, {0, -1e9,0}, true,  aGL::Colors::White));

}


Raytracer::~Raytracer()
{
    for(size_t i = 0; i < objlist_.size(); ++i)
        delete objlist_[i];
}

aGL::Color Raytracer::getRayColor(const mgm::Ray3f& ray, int depth) const
{
    if(depth > qS_.maxRayRefl){
        return aGL::Colors::Black;
    }

    RTObjs::SurfacePoint pt = {};
    size_t crossObj = 0;
    double distance = RTObjs::NoIntersection;

    for(size_t i = 0; i < objlist_.size(); ++i){
        double curDistance = objlist_[i]->getIntersection(ray);
        if(!mgm::isZero(curDistance) && curDistance < distance){
            distance = curDistance;
            crossObj = i;
        }
    }
    if(distance == RTObjs::NoIntersection) // It seems unsafe but NoInertsecton is +INF so it's ok.
    {   
        return (depth != 0) ? aGL::Colors::Black : getSkyGradient(ray.dir());
    }

    objlist_[crossObj]->getIntersection(ray, &pt);

    if(pt.isSource){
        return pt.color; // * mgm::randomDouble(0.95, 1.105);
    }
    

    mgm::Vector3f refVec = ray.dir();
    refVec *= -1;

    if((refVec * pt.normal < -mgm::EPS || pt.isInside) && depth > 5)
        return aGL::Colors::Black;

    if(refVec * pt.normal < -mgm::EPS)
        mError << depth << " " << ray << " " << pt.normal << " " << pt.point << mlg::endl;
    mAssert(refVec * pt.normal >= -mgm::EPS);
    

    refVec = mgm::getReflection(refVec, pt.normal);

    mAssert(refVec * pt.normal >= -mgm::EPS);
    mAssert(pt.isInside == false);
    
    // Vec wave = mgm::normalize(pt.normal);
    // wave *= 1.1 * mgm::EPS;
    // pt.point += wave;

    aGL::Color refRayColor = getRayColor(mgm::Ray3f{pt.point, refVec}, depth + 1);
    
    aGL::Color resultColor = ambient_;

    resultColor += refRayColor * pt.reflCoef;
    resultColor &= pt.color;

    resultColor += getTrueLambert(pt, depth + 1) * pt.diffCoef;
    
    // mAssert(refRayColor.a() == 255);
    return resultColor;
}


void Raytracer::onPaintEvent() const 
{
    if(isRendered) return;
    // surface->clear(aGL::Colors::Black);

    for(uint32_t x = 0; x < rect_.w; ++x)
    {
        for(uint32_t y = 0; y < rect_.h; ++y)
        {
            mgm::Ray3f ray(camera_, mgm::Point3f((x - 0.5 * rect_.w), (y - 0.5 * rect_.h), 0.));

            AvgColor antialiasing{};
            antialiasing += getRayColor(ray);
            for(uint32_t i = 0; i < qS_.antialiasingLvl; ++i)
            {
                Vec aliasDir = ray.dir();
                Vec aliasShift = {mgm::randomDouble(-1, 1), mgm::randomDouble(-1, 1), 0};
                aliasShift *= qS_.antialiasMaxShift;
                aliasDir += aliasShift;
                Ray aliasRay(camera_, aliasDir);
                antialiasing += getRayColor(aliasRay);
            }

            surface->drawPoint({x, y}, aGL::gammaCorrect(antialiasing.getAvg(), qS_.gamma));
            // mInfo << "Point " << x << ' ' << y << " gotten" << mlg::endl;
        }
            render(*wind);
            wind->update();
    }
}

aGL::Color Raytracer::getTrueLambert(const RTObjs::SurfacePoint& surfPoint, int depth) const 
{
    AvgColor avg = {};

    uint64_t nRays = (depth < qS_.lamberthFastEdge) ? qS_.lamberthDepth : (labertianDepth_ / 10);

    for(uint64_t i = 0; i < nRays; ++i)
    {
        Vec dir = surfPoint.normal;
        dir += mgm::randomInSphere();
        Point pt = surfPoint.point;
        pt += dir;
        Color col = getRayColor({pt, dir}, depth + qS_.lamberthReflCost); 
        avg += col;
    }

    Color ret = avg.getAvg();
    ret &= surfPoint.color;
    return ret;
}

aGL::Color Raytracer::getLambert(const RTObjs::SurfacePoint& surfPoint) const 
{
    aGL::Color lambert = aGL::Colors::Black;
    for(size_t i = 0; i < objlist_.size(); ++i){
        if(objlist_[i]->isSource_)
        {
            bool isShadow = false;
            double dist = objlist_[i]->getIntersection({surfPoint.point, objlist_[i]->getCenter()});
            for(size_t j = 0; j < objlist_.size(); ++j){
                if(i != j){
                    if(dist > objlist_[j]->getIntersection({surfPoint.point, objlist_[i]->getCenter()}))
                    {
                        isShadow = true;
                        break;
                    }
                }
            }
            if(isShadow) continue;
            double intensy = std::max(0., ((mgm::normalize(objlist_[i]->getCenter() - surfPoint.point) * surfPoint.normal) / surfPoint.normal.len()));
            assert(intensy < 1);
            lambert += objlist_[i]->getColor() * intensy;
        }
    }

    return lambert &= surfPoint.color;
}

Raytracer::Color Raytracer::getSkyGradient(const Vec& v)
{
    double t = 0.5 * (mgm::normalize(v).y + 1);
    // mDebug << t << mlg::endl;
    return (1. - t) * aGL::Colors::White + (t)*(Color(0x78B2FFFF)); 
}


