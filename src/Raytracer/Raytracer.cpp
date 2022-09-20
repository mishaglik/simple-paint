#include "Raytracer.hpp"
#include "RenderSphere.hpp"
#include <iostream>


Raytracer::Raytracer(uint32_t x, uint32_t y, uint32_t w, uint32_t h) : aGL::Widget({x, y, w, h}), camera_({0, 0, -1000}) {
    objlist_    = new RTObjs::RenderObject* [2];
    objlist_[0] = new RTObjs::RenderSphere({0,     0, 1000}, 250, false, aGL::Colors::Yellow);
    objlist_[1] = new RTObjs::RenderSphere({0,  -1e5, 1000}, 9e4, true,  aGL::Colors::White);
}


Raytracer::~Raytracer(){
    delete objlist_[0];
    delete objlist_[1];
    delete[] objlist_;
}

aGL::Color Raytracer::getRayColor(const mgm::Ray3f& ray, int depth) const {
    if(depth > 128){
        return aGL::Colors::Blue;
    }

    RTObjs::SurfacePoint pt = {};
    size_t crossObj = 0;
    double distance = RTObjs::NoIntersection;

    for(size_t i = 0; i < 2; ++i){
        double curDistance = objlist_[i]->getIntersection(ray);
        if(curDistance < distance){
            distance = curDistance;
            crossObj = i;
        }
    }
    if(distance == RTObjs::NoIntersection){
        return (depth == 0) ? aGL::Colors::Black : aGL::Colors::DGray;
    }
    // std::cerr << crossObj << '\n';
    // assert(crossObj == 0);
    // return aGL::Color(0, static_cast<uint8_t>(std::min(distance / 20, 255.)), 0, 255);
    objlist_[crossObj]->getIntersection(ray, &pt);
    if(pt.isSource){
        return pt.color;
    }

    mgm::Vector3f refVec = ray.dir();
    refVec *= -1;
    refVec = mgm::getReflection(refVec, pt.normal);

    assert(refVec * pt.normal >= 0);

    pt.point += normalize(refVec);

    // if(fabs(ray.dir().x) < 1){
        // std::cerr << refVec.x << ' ' << refVec.y << ' ' << refVec.z << '\n'; 
    // }

    return pt.color &= getRayColor(mgm::Ray3f{pt.point, refVec}, depth + 1);
}


void Raytracer::onPaintEvent() const {
    surface->clear(aGL::Colors::Black);

    for(uint32_t x = 0; x < rect_.w; ++x){
        for(uint32_t y = 0; y < rect_.h; ++y){
            mgm::Ray3f ray(camera_, mgm::Point3f((x - 0.5 * rect_.w), (y - 0.5 * rect_.h), 0.));
            surface->drawPoint({x, y}, getRayColor(ray));
        }
    }
}
