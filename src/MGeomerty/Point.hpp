#ifndef MGEOMETRY_POINT_HPP
#define MGEOMETRY_POINT_HPP
#include <cassert>
#include <cstdint>
#include <math.h>

namespace mgm {

    /**
     * @brief The Point2 class
     */
    template <typename num_t>
    struct Point2
    {
        num_t x, y;

        /**
         * @brief Point2 - point on surface
         * @param _x - x coordinate
         * @param _y - y coordinate
         */
        Point2(num_t _x, num_t _y) : x(_x), y(_y) {}

        /**
         * @brief Point2 default constructor (0, 0)
         */
        Point2() : Point2(0, 0) {}

        /**
         * @brief Point2 constructor from point of other type
         * @param point ------------------^
         */
        template <typename T>
        Point2(const Point2<T>& point) : x(point.x), y(point.y) {}
    };

    /**
     * @brief The Point3 class
     */
    template <typename num_t>
    struct Point3
    {
        num_t x, y, z;

        /**
         * @brief Point3
         * @param _x - x coordiante
         * @param _y - y coordiante
         * @param _z - z coordiante
         */
        Point3(num_t _x, num_t _y, num_t _z) : x(_x), y(_y), z(_z) {}

        /**
         * @brief Point3 default constructor (0,0,0)
         */
        Point3() : Point3(0, 0, 0) {}

        /**
         * @brief Point3 constructor from Point2
         * @param pt - Point2 point
         */
        Point3(const Point2<num_t>& pt, num_t _z = 0) : x(pt.x), y(pt.y), z(_z) {}

        /**
         * @brief Point3 constructor from point of other type
         * @param pt ---------------------^
         */
        template <typename T>
        Point3(const Point3<T>& pt) : x(pt.x), y(pt.y), z(pt.z) {}
};

    using Point2f = Point2<double>;
    using Point2u = Point2<uint32_t>;
    using Point2i = Point2<int32_t>;


    using Point3f = Point3<double>;
    using Point3u = Point3<uint32_t>;
    using Point3i = Point3<int32_t>;

    bool operator==(const Point2f& lhs, const Point2f& rhs);
    bool operator==(const Point3f& lhs, const Point3f& rhs);

    bool operator!=(const Point2f& lhs, const Point2f& rhs);
    bool operator!=(const Point3f& lhs, const Point3f& rhs);

} // namespace mgm
#endif
