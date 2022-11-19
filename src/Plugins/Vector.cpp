#include "Vector.hpp"

namespace mgm {
Vector2f normalize(const Vector2f& v_){
    Vector2f v = v_;
    if(v*v < EPS) {
        v.x = v.y = 0;
        return v;
    }
    return v /= v.len();
}

Vector3f normalize(const Vector3f& v_){
    Vector3f v = v_;
    if(v*v < EPS) {
        v.x = v.y = v.z = 0;
        return v;
    }
    return v /= v.len();
}

bool operator==(const Vector2f& lhs, const Vector2f& rhs){
    return isZero(lhs.x - rhs.x) && isZero(lhs.y - rhs.y);
}
bool operator==(const Vector3f& lhs, const Vector3f& rhs){
    return isZero(lhs.x - rhs.x) && isZero(lhs.y - rhs.y) && isZero(lhs.z - rhs.z);
}


}

