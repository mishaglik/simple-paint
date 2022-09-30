#include "Raytracer.hpp"
#include <iostream>
#include "ColorAvg.hpp"

#include <thread>
#include <mutex>

Raytracer::Raytracer(uint32_t x, uint32_t y, uint32_t w, uint32_t h) : aGL::Widget({x, y, w, h}), camera_({0, 0, -1000})
{
    #ifdef RAYTRACER_MULTITHREADING
        multithreadContext_ = new MulithreadContext{};
        multithreadContext_->rt = this;
        
        for(size_t i = 0; i < nThreads; ++i)
        {
            threads[i] = new std::thread(Raytracer::raytraceThread, multithreadContext_);
        }
    #endif
}

void Raytracer::raytraceThread(MulithreadContext* context)
{
    uint32_t x = 0;
    uint32_t w = context->rt->getRect().w;
    while (1)
    {
        context->xMutex.lock();
        x = context->x0++;
        if(x >= w)
        {
            x = context->x0 = 0;
        }
        context->xMutex.unlock();

        context->rt->paintSegment(x, 1);
    }
}


Raytracer::~Raytracer()
{
#ifdef RAYTRACER_MULTITHREADING
    for(size_t i = 0; i < nThreads; ++i)
    {
        delete threads[i];
    }
    delete multithreadContext_;
#endif

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
        // return (depth != 0) ? ambient_ : getSkyGradient(ray.dir());
        return ambient_;
    }

    objlist_[crossObj]->getIntersection(ray, &pt);

    if(pt.material->isSource){
        return pt.material->srcColor;
    }
    
    aGL::Color resultColor = aGL::Colors::Black;

    if(!mgm::isZero(pt.material->reflCoef) && !pt.isInside)
    {
        mgm::Vector3f refVec = ray.dir();
        refVec *= -1;

        if(refVec * pt.normal < -mgm::EPS)
            mError << depth << " " << ray << " " << pt.normal << " " << pt.point << mlg::endl;
        mAssert(refVec * pt.normal >= -mgm::EPS);
        

        refVec = mgm::getReflection(refVec, pt.normal);

        mAssert(refVec * pt.normal >= -mgm::EPS);
        
        aGL::Color refRayColor = getRayColor(mgm::Ray3f{pt.point, refVec}, depth + 1) * pt.material->reflCoef;

        refRayColor &= pt.material->color;
        resultColor += refRayColor;
    } /* endif direct reflection. */

    if(!mgm::isZero(pt.material->diffCoef) && !pt.isInside)
    {
        resultColor += getTrueLambert(pt, depth + 1) * pt.material->diffCoef;
    }
    
    if(!mgm::isZero(pt.material->refrCoef))
    {
        double  inRefrIndex = 1;
        double outRefrIndex = pt.material->refrIndex;
        
        if(pt.isInside) std::swap(inRefrIndex, outRefrIndex);

        Vec v = mgm::normalize(ray.dir());

        double sinF = sqrt(1 - (v * pt.normal) * (v * pt.normal));
        mAssert(!std::isnan(sinF));

        if((inRefrIndex * sinF / outRefrIndex) < 1 - mgm::EPS)
        {
            mAssert(v * pt.normal < mgm::EPS);
            Vec parrallel = pt.normal;
            parrallel *= v * pt.normal;

            Vec orthogonal = v;
            orthogonal -= parrallel;

            mAssert(mgm::isZero(orthogonal.len() - sinF));

            orthogonal *= inRefrIndex / outRefrIndex;

            parrallel = pt.normal;
            parrallel *= -sqrt(1 - orthogonal.len2());

            orthogonal += parrallel;

            Point startPt = pt.point;

            aGL::Color refrColor = getRayColor({startPt, orthogonal}, depth + 1/*XXX*/) * pt.material->refrCoef;
            //TODO: Color adjustment
            resultColor += refrColor;

        } 
        else /* Full reflection */  //XXX: This is copy of reflection. Do smth with it.
        {
            v *= -1;
            v = mgm::getReflection(v, pt.normal);
            aGL::Color refRayColor = getRayColor(mgm::Ray3f{pt.point, v}, depth + 1) * pt.material->refrCoef;
            refRayColor &= pt.material->color;
            resultColor += refRayColor;
            mAssert(pt.isInside);
        }
    }

    // mAssert(refRayColor.a() == 255);
    return resultColor;
}

void Raytracer::onPaintEvent() const 
{
    if(isRendered) return;
#ifdef RAYTRACER_MULTITHREADING
    return;
#else
    for(uint32_t x = 0; x < rect_.w; x++)
    {  
        paintSegment(x, 1);
        // render(*wind);  //HACK:
        // wind->update();
    }
#endif
}

void Raytracer::paintSegment(uint32_t x0, uint32_t w0) const
{
    if(isRendered) return;
    for(uint32_t x = x0; x < x0 + w0; ++x)
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
        
        #ifdef RAYTRACER_MULTITHREADING
            multithreadContext_->drawMutex.lock();
        #endif

            surface->drawPoint({x, y}, aGL::gammaCorrect(antialiasing.getAvg(), qS_.gamma));
            // mInfo << "Point " << x << ' ' << y << " gotten" << mlg::endl;

        #ifdef RAYTRACER_MULTITHREADING
            multithreadContext_->drawMutex.unlock();
        #endif
        }

    #ifndef RAYTRACER_MULTITHREADING
        render(*wind);  //HACK:
        wind->update();
    #endif
        mInfo << mlg::Logger::CoStyle::Green <<"Done layer: " << x << mlg::endl;
    }
}


aGL::Color Raytracer::getTrueLambert(const RTObjs::SurfacePoint& surfPoint, int depth) const 
{
    AvgColor avg = {};

    uint64_t nRays = (depth < qS_.lamberthFastEdge) ? qS_.lamberthDepth : (qS_.lamberthDepth / 10);

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
    // ret |= ambient_;
    ret &= surfPoint.material->color;
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

    return lambert &= surfPoint.material->color;
}

Raytracer::Color Raytracer::getSkyGradient(const Vec& v)
{
    if(v.z < 0 || v.y > 0) return aGL::Colors::Red;
    double t = 0.5 * (mgm::normalize(v).y + 1);
    // mDebug << t << mlg::endl;
    return (1. - t) * aGL::Colors::White + (t)*(Color(0x78B2FFFF)); 
}


void Raytracer::addObject(RenderObject* object)
{
    objlist_.push_back(object);
}

