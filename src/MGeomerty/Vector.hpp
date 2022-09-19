#ifndef MGEOMETRY_VECTOR_HPP
#define MGEOMETRY_VECTOR_HPP
#include <MGeomerty/Float.hpp>
#include <cassert>
#include <cmath>
#include <math.h>

namespace mgm {

template<typename num_t>
class Vector2{
private:
public:
    num_t x, y;

    Vector2(num_t _x, num_t _y) : x(_x), y(_y) {}
    Vector2() : Vector2(0, 0) {}

    template<typename T>
    Vector2(const Vector2<T>& oth) : x(static_cast<num_t>(oth.x)), y(static_cast<num_t>(oth.y)) {}

    double len() const {return sqrt(x*x + y*y);}

    Vector2<num_t>& operator+= (const Vector2<num_t> &rhs){
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vector2<num_t>& operator*= (num_t rhs){
        x *= rhs;
        y *= rhs;
        return *this;
    } 

    Vector2<num_t>& operator/= (num_t rhs){
        x /= rhs;
        y /= rhs;
        return *this;
    } 
};

template<typename num_t>
Vector2<num_t> getOrthogonal(const Vector2<num_t>& v){
    return Vector2<num_t>{-v.y, v.x};
}


template<typename num_t>
class Vector3{
private:
public:
    num_t x, y, z;

    Vector3(num_t _x, num_t _y, num_t _z) : x(_x), y(_y), z(_z) {}
    Vector3() : Vector3(0, 0, 0) {}

    Vector3(const Vector2<num_t>& v) : Vector3(v.x, v.y, 0) {}
    
    template<typename T>
    Vector3(const Vector3<T>& oth) : x(static_cast<num_t>(oth.x)), y(static_cast<num_t>(oth.y)), z(static_cast<num_t>(oth.z)) {}

    double len() const {return sqrt(x*x + y*y + z*z);}

    Vector3<num_t>& operator+= (const Vector3<num_t> &rhs){
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    Vector3<num_t>& operator*= (num_t rhs){
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    } 

    Vector3<num_t>& operator/= (num_t rhs){
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    } 
};

template<typename num_t>
num_t operator*(const Vector2<num_t>& v1, const Vector2<num_t>& v2){
    return v1.x * v2.x +
           v1.y * v2.y;
}

template<typename num_t>
num_t operator*(const Vector3<num_t>& v1, const Vector3<num_t>& v2){
    return v1.x * v2.x +
           v1.y * v2.y +
           v1.z * v2.z;
}

template<typename num_t>
num_t operator^(const Vector2<num_t>& v1, const Vector2<num_t>& v2){
    return v1.x * v2.y - v1.y * v2.x;
}

template<typename num_t>
Vector3<num_t> operator^(const Vector3<num_t>& v1, const Vector3<num_t>& v2){
    return Vector3<num_t>{
    v1.y * v2.z - v1.z * v2.y,
    v1.z * v2.x - v1.x * v2.z,
    v1.x * v2.y - v1.y * v2.x,
    };
}

template<typename num_t>
bool isParallel(const Vector2<num_t>& v1, const Vector2<num_t>& v2){
    return isZero(v1 ^ v2);
}

template<typename num_t>
bool isParallel(const Vector3<num_t>& v1, const Vector3<num_t>& v2){
    return isZero((v1 ^ v2).len());
}

template<typename num_t>
bool isCollin(const Vector2<num_t>& v1, const Vector2<num_t>& v2){
    return isParallel(v1, v2) && (v1 * v2) >= 0;
}

template<typename num_t>
bool isCollin(const Vector3<num_t>& v1, const Vector3<num_t>& v2){
    return isParallel(v1, v2) && (v1 * v2) >= 0;
}

template<typename num_t>
bool operator||(const Vector2<num_t>& v1, const Vector2<num_t>& v2){
    return isParallel(v1, v2);
}

template<typename num_t>
bool operator||(const Vector3<num_t>& v1, const Vector3<num_t>& v2){
    return isParallel(v1, v2);
}

using Vector2f = Vector2<double>;
using Vector2i = Vector2<int>;
using Vector2u = Vector2<unsigned>;

using Vector3f = Vector3<double>;
using Vector3i = Vector3<int>;
using Vector3u = Vector3<unsigned>;

Vector2f normalize(const Vector2f& v);
Vector3f normalize(const Vector3f& v);

Vector2f rotate(const Vector2f& v, double a);
Vector3f rotateZ(const Vector3f& v, double a);

bool operator==(const Vector2f& lhs, const Vector2f& rhs);
bool operator==(const Vector3f& lhs, const Vector3f& rhs);

inline bool operator!=(const Vector2f& lhs, const Vector2f& rhs) {return !(lhs == rhs);}
inline bool operator!=(const Vector3f& lhs, const Vector3f& rhs) {return !(lhs == rhs);}

}
#endif
