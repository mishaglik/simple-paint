#include "Raycaster.hpp"
#include "AbstractGL/AWindow.hpp"
#include "AbstractGL/Widget.hpp"
#include "MGeomerty/Geometry.hpp"
#include "MGeomerty/Point.hpp"
#include "MGeomerty/Vector.hpp"
#include <SFML/Graphics/Color.hpp>
#include <cstdint>
#include <iostream>

Raycaster::Raycaster(uint32_t x, uint32_t y, uint32_t size) :
    aGL::Widget({x, y, size, size}), cs_({x, y, size, size}, {-2, 2}, {2, -2}),
    camera_({0, 0, 20}), light_({10, 0, 3})
{

}

void Raycaster::render(const aGL::Window& window){

    for(uint32_t x = rect_.x; x < rect_.x + rect_.w; ++x){
        for(uint32_t y = rect_.y; y < rect_.y + rect_.h; ++y){
            mgm::Point3f ballPoint = cs_.rTransform({x, y});
            aGL::ColorARGB color = 0x00000000;        
            
            if(ballPoint.x * ballPoint.x + ballPoint.y * ballPoint.y <= 1){
                ballPoint.z = 1 - mgm::radiusLen(ballPoint);

                mgm::Vector3f lightVect = mgm::rotateZ(light_, angle_) - ballPoint;
                mgm::Vector3f normal    = ballPoint - mgm::Point3f(0, 0, 0);
                mgm::Vector3f view      = camera_ - ballPoint;

                mgm::normalize(lightVect);
                mgm::normalize(view);

                uint8_t ligthness = 0x1a;

                double dynamic = (lightVect * normal);
                dynamic = std::max(0.0, dynamic);
                
                ligthness += static_cast<uint8_t>(dynamic * 180);

                normal    *= 2 * (lightVect * normal);
                lightVect *= -1;
                normal    += lightVect;

                double blik = std::pow(std::max(normal * view, 0.), 11);
                ligthness += static_cast<uint8_t>(std::min(50.,(blik * 400000)));



                color.r_ = ligthness;
                color.g_ = ligthness;
                color.b_ = ligthness;
                color.a_ = 0xFF;
            }

            window.drawPoint({x,y}, color);
        }
    }
}

void Raycaster::addAngle(double angle){
    angle_ += angle;
}

int Raycaster::handleEvent(const aGL::Event& event){
    if(event.type == aGL::EventType::Press){
        double z = light_.z;
        light_ = cs_.rTransform(event.data.pt);
        light_.x *= 5;
        light_.y *= 5;
        light_.z = z;
        angle_ = 0;
    }
    return 1;
}

