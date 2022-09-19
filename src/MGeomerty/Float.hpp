#ifndef MGEOMERTY_FLOAT_HPP
#define MGEOMERTY_FLOAT_HPP

#include <cmath>

#ifndef MGEOMERTY_EPSILON
#define MGEOMERTY_EPSILON 1e-6
#endif

namespace mgm {
    const double EPS = MGEOMERTY_EPSILON;

    inline bool isZero(int x){
        return x == 0;
    }
    
    inline bool isZero(double x){
        return fabs(x) < EPS;
    }
}

#endif /* MGEOMERTY_FLOAT_HPP */
