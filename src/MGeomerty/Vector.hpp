#ifndef MGEOMETRY_VECTOR_HPP
#define MGEOMETRY_VECTOR_HPP
#include <cassert>
#include <cmath>
#include <math.h>

namespace mgm {
const double EPS = 1e-6;

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

typedef Vector2<double>   Vector2f;
typedef Vector2<int   >   Vector2i;
typedef Vector2<unsigned> Vector2u;

typedef Vector3<double>   Vector3f;
typedef Vector3<int   >   Vector3i;
typedef Vector3<unsigned> Vector3u;

inline Vector2f& normalize(Vector2f& v){
    if(v*v < EPS) {
        v.x = v.y = 0;
        return v;
    }
    return v /= v.len();
}

inline Vector3f& normalize(Vector3f& v){
    if(v*v < EPS) {
        v.x = v.y = v.z = 0;
        return v;
    }
    return v /= v.len();
}

Vector2f rotate(const Vector2f& v, double a);
Vector3f rotateZ(const Vector3f& v, double a);
}
#endif
