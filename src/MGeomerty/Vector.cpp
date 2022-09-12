#include "Vector.hpp"
namespace mgm {

Vector2f rotate(const Vector2f& v, double a){
    return {
         v.x * cos(a) + v.y * sin(a),
        -v.x * sin(a) + v.y * cos(a),
        };
}

Vector3f rotateZ(const Vector3f& v, double a){
    return {
         v.x * cos(a) + v.y * sin(a),
        -v.x * sin(a) + v.y * cos(a),
         v.z
        };
}

}

