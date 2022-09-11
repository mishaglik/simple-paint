#ifndef MGEOMETRY_VECTOR_HPP
#define MGEOMETRY_VECTOR_HPP
#include <cassert>
#include <math.h>

namespace mgm {

template<typename num_t>
class Vector2{
private:
    num_t x_, y_;
public:

    Vector2(num_t x, num_t y) : x_(x), y_(y) {}
    Vector2() : Vector2(0, 0) {}

    double len() const {return sqrt(x_*x_ + y_*y_);}

    Vector2<num_t>& operator+= (const Vector2<num_t> &rhs){
        x_ += rhs.x_;
        y_ += rhs.y_;
        return *this;
    }

    Vector2<num_t>& operator*= (num_t rhs){
        x_ *= rhs;
        y_ *= rhs;
        return *this;
    } 

    Vector2<num_t>& operator/= (num_t rhs){
        assert(rhs != 0);
        x_ /= rhs;
        y_ /= rhs;
        return *this;
    } 
};

typedef Vector2<double>   Vector2f;
typedef Vector2<int   >   Vector2i;
typedef Vector2<unsigned> Vector2u;

}
#endif
