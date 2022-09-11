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
num_t operator*(const Vector2<num_t>& v1, const Vector2<num_t>& v2){
    return v1.x * v2.x +
           v1.y * v2.y;
}

typedef Vector2<double>   Vector2f;
typedef Vector2<int   >   Vector2i;
typedef Vector2<unsigned> Vector2u;

inline Vector2f& normalize(Vector2f& v){
    if(v*v < EPS) {
        v.x = v.y = 0;
        return v;
    }
    return v /= v.len();
}

Vector2f rotate(const Vector2f& v, double a);

}
#endif
