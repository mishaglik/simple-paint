#ifndef MGEOMETRY_VECTOR_HPP
#define MGEOMETRY_VECTOR_HPP
#include <cmath>
#include <math.h>

#ifndef MGEOMERTY_EPSILON
#define MGEOMERTY_EPSILON 1e-8
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

namespace mgm {

    /**
     * @brief The Vector2 class
     */
    template<typename num_t>
    class Vector2
    {

    public:
        num_t x, y;

        Vector2(num_t _x, num_t _y) : x(_x), y(_y) {}
        Vector2() : Vector2(0, 0) {}

        template<typename T>
        Vector2(const Vector2<T>& oth) : x(oth.x), y(oth.y) {}

        double len () const {return sqrt(x*x + y*y);}
        num_t len2() const {return      x*x + y*y ;}

        Vector2<num_t>& operator+= (const Vector2<num_t> &rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        Vector2<num_t>& operator-= (const Vector2<num_t> &rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        Vector2<num_t>& operator*= (num_t rhs)
        {
            x *= rhs;
            y *= rhs;
            return *this;
        }

        Vector2<num_t>& operator/= (num_t rhs)
        {
            x /= rhs;
            y /= rhs;
            return *this;
        }

        bool operator< (const Vector2& rhs) const
        {
            return (x == rhs.x) ? (y < rhs.y) : (x < rhs.x);
        }
    };

    /**
     * @brief getOrthogonal - create vector orthogonal to given
     * @param v - base vector
     * @return orthogonal to v
     */
    template<typename num_t>
    Vector2<num_t> getOrthogonal(const Vector2<num_t>& v)
    {
        return Vector2<num_t>{-v.y, v.x};
    }

    /**
     * @brief The Vector3 class
     */
    template<typename num_t>
    class Vector3{
    public:
        num_t x, y, z;

        Vector3(num_t _x, num_t _y, num_t _z) : x(_x), y(_y), z(_z) {}

        Vector3() : Vector3(0, 0, 0) {}

        Vector3(const Vector2<num_t>& v) : Vector3(v.x, v.y, 0) {}

        template<typename T>
        Vector3(const Vector3<T>& oth) : x(oth.x), y(oth.y), z(oth.z) {}

        double len () const {return sqrt(x*x + y*y + z*z);}
        double len2() const {return     (x*x + y*y + z*z);}

        Vector3<num_t>& operator+= (const Vector3<num_t> &rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        Vector3<num_t>& operator-= (const Vector3<num_t> &rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        Vector3<num_t>& operator*= (num_t rhs)
        {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }

        Vector3<num_t>& operator/= (num_t rhs)
        {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            return *this;
        }
    };

    /**
     * @brief dotProd - scalar multiplication of two vectors.
     * @param v1 - first vector
     * @param v2 - second vector
     * @return (v1, v2)
     */
    template<typename num_t>
    num_t dotProd(const Vector2<num_t>& v1, const Vector2<num_t>& v2)
    {
        return v1.x * v2.x +
               v1.y * v2.y;
    }

    /**
     * @brief dotProd - scalar multiplication of two vectors.
     * @param v1 - first vector
     * @param v2 - second vector
     * @return (v1, v2)
     */
    template<typename num_t>
    num_t dotProd(const Vector3<num_t>& v1, const Vector3<num_t>& v2)
    {
        return v1.x * v2.x +
               v1.y * v2.y +
               v1.z * v2.z;
    }

    /**
     * @brief operator * alias to dotprod
     */
    template<typename num_t>
    num_t operator* (const Vector2<num_t>& v1, const Vector2<num_t>& v2)
    {
        return dotProd(v1, v2);
    }

    /**
     * @brief operator * alias to dotprod
     * @ref dotProd
     */
    template<typename num_t>
    num_t operator* (const Vector3<num_t>& v1, const Vector3<num_t>& v2)
    {
        return dotProd(v1, v2);
    }

    /**
     * @brief crossProd return z value of vector multiplication
     * It's equal to |v1| * |v2| * sin angle(v1, v2).
     * @param v1 - first
     * @param v2 - second
     * @return z value of vector multiplication == |[v1, v2]|
     */
    template<typename num_t>
    num_t crossProd(const Vector2<num_t>& v1, const Vector2<num_t>& v2){
        return v1.x * v2.y - v1.y * v2.x;
    }

    /**
     * @brief crossProd - vector multiplication of two vectors.
     * @param v1 - lhs
     * @param v2 - rhs
     * @return [v1, v2]
     */
    template<typename num_t>
    Vector3<num_t> crossProd(const Vector3<num_t>& v1, const Vector3<num_t>& v2){
        return Vector3<num_t>{
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x,
        };
    }

    template<typename num_t>
    num_t operator^ (const Vector2<num_t>& v1, const Vector2<num_t>& v2){
        return crossProd(v1, v2);
    }

    template<typename num_t>
    Vector3<num_t> operator^(const Vector3<num_t>& v1, const Vector3<num_t>& v2){
         return crossProd(v1, v2);
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

    bool operator==(const Vector2f& lhs, const Vector2f& rhs);
    bool operator==(const Vector3f& lhs, const Vector3f& rhs);

    inline bool operator!=(const Vector2f& rhs, const Vector2f& lhs) {return !(lhs == rhs);}
    inline bool operator!=(const Vector3f& lhs, const Vector3f& rhs) {return !(lhs == rhs);}
}
#endif
