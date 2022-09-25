#include "Raytracer.hpp"
#include "RenderSphere.hpp"
#include "RenderPlane.hpp"
#include <iostream>


Raytracer::Raytracer(uint32_t x, uint32_t y, uint32_t w, uint32_t h) : aGL::Widget({x, y, w, h}), camera_({0, 0, -1000}) {
    nObjects = 5;
    objlist_    = new RTObjs::RenderObject* [nObjects];
    objlist_[0] = new RTObjs::RenderPlane ({   0,     1,   0.05}, {0, 150,0}, false,  0x00a520ff);
    objlist_[1] = new RTObjs::RenderSphere({   0,     0, 1000}, 100, false, aGL::Colors::Magenta);
    objlist_[2] = new RTObjs::RenderSphere({ 300,     0, 1000}, 100, false, aGL::Colors::LGray);
    objlist_[3] = new RTObjs::RenderSphere({   0,  -1e5, 1000}, 1e4, true,  aGL::Colors::White);
    objlist_[4] = new RTObjs::RenderSphere({ 155,  -300, 1000},  40, true,  aGL::Colors::Yellow);
    // objlist_[5] = new RTObjs::RenderPlane({    0,  1, 0}, {0, -1e5, 0}, true,  aGL::Colors::White);
}


Raytracer::~Raytracer(){
    for(size_t i = 0; i < nObjects; ++i)
        delete objlist_[i];

    delete[] objlist_;
}

aGL::Color Raytracer::getRayColor(const mgm::Ray3f& ray, int depth) const {
    if(depth > 128){
        return aGL::Colors::Blue;
    }

    RTObjs::SurfacePoint pt = {};
    size_t crossObj = 0;
    double distance = RTObjs::NoIntersection;

    for(size_t i = 0; i < nObjects; ++i){
        double curDistance = objlist_[i]->getIntersection(ray);
        if(curDistance < distance){
            distance = curDistance;
            crossObj = i;
        }
    }
    if(distance == RTObjs::NoIntersection){
        // return aGL::Colors::Black;
        return (depth != 0) ? aGL::Colors::Black : aGL::Color(0x3425c7ff);
    }
    // std::cerr << crossObj << '\n';
    // assert(crossObj == 0);
    // return aGL::Color(0, static_cast<uint8_t>(std::min(distance / 20, 255.)), 0, 255);
    objlist_[crossObj]->getIntersection(ray, &pt);
    if(pt.isSource){
        return pt.color;
    }
    
    // return (pt.normal * mgm::Vector3f{0,1,0} > 0) ? aGL::Colors::Red : aGL::Colors::Green;

    mgm::Vector3f refVec = ray.dir();
    refVec *= -1;

    assert(refVec * pt.normal >= -mgm::EPS);
    refVec = mgm::getReflection(refVec, pt.normal);

    assert(refVec * pt.normal >= 0 );

    pt.point += normalize(refVec);
   
    // assert(!reinterpret_cast<RTObjs::RenderSphere*>(objlist_[crossObj])->sph_.contains(pt.point));
    // for(size_t i = 0; i < nObjects; ++i){
        // assert(!reinterpret_cast<RTObjs::RenderSphere*>(objlist_[i])->sph_.contains(pt.point));
    // }

    // if(fabs(ray.dir().x) < 1){
        // std::cerr << refVec.x << ' ' << refVec.y << ' ' << refVec.z << '\n'; 
    // }

    aGL::Color refRayColor = getRayColor(mgm::Ray3f{pt.point, refVec}, depth + 1);
    
    aGL::Color resultColor = ambient_;

    resultColor += refRayColor * pt.reflCoef;
    resultColor &= pt.color;

    resultColor += getLambert(pt) * pt.refrCoef;
    assert(refRayColor.a() == 255);

    // return getLambert(pt) += refRayColor;
    return resultColor;
    // return pt.color &= getRayColor(mgm::Ray3f{pt.point, refVec}, depth + 1);
}


void Raytracer::onPaintEvent() const {
    if(isRendered) return;
    surface->clear(aGL::Colors::Black);

    for(uint32_t x = 0; x < rect_.w; ++x){
        for(uint32_t y = 0; y < rect_.h; ++y){
            mgm::Ray3f ray(camera_, mgm::Point3f((x - 0.5 * rect_.w), (y - 0.5 * rect_.h), 0.));
            surface->drawPoint({x, y}, getRayColor(ray));
        }
    }
}


aGL::Color Raytracer::getLambert(const RTObjs::SurfacePoint& surfPoint) const {
    aGL::Color lambert = aGL::Colors::Black;
    for(size_t i = 0; i < nObjects; ++i){
        if(objlist_[i]->isSource_){

            bool isShadow = false;
            double dist = objlist_[i]->getIntersection({surfPoint.point, objlist_[i]->getCenter()});
            for(size_t j = 0; j < nObjects; ++j){
                if(i != j){
                    if(dist > objlist_[j]->getIntersection({surfPoint.point, objlist_[i]->getCenter()})){
                        isShadow = true;
                        break;
                    }
                }
            }
            if(isShadow) continue;
            double intensy = std::max(0., ((mgm::normalize(objlist_[i]->getCenter() - surfPoint.point) * surfPoint.normal) / surfPoint.normal.len()));
            assert(intensy < 1);
            if(objlist_[i]->getColor() == aGL::Colors::Blue){
                // std::cerr << intensy << ' ';
                // std::cerr << i << ' ' << std::hex << objlist_[i]->getColor() * intensy << std::dec << '\n';
            }
            lambert += objlist_[i]->getColor() * intensy;
        }
    }

    return lambert &= surfPoint.color;
}
