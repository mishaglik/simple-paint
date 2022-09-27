#ifndef MGEOMERTY_GEOMETRY_HPP
#define MGEOMERTY_GEOMETRY_HPP

#include <MGeomerty/Vector.hpp>
#include <MGeomerty/Point.hpp>
#include <MGeomerty/Rect.hpp>
#include <MGeomerty/Line.hpp>
#include <MGeomerty/Sphere.hpp>
#include <MGeomerty/Intersects.hpp>
#include <MGeomerty/Operations.hpp>
#include <random>
#include <LogUtils/LogUtils.hpp>

namespace mgm {

    inline double randomDouble() {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }

    inline double randomDouble(double min, double max) {
        return min + (max-min)*randomDouble();
    }

    inline Vector3f randomInSphere(){
        Vector3f v{};
        do{
            v = {
                randomDouble(-1, 1),
                randomDouble(-1, 1),
                randomDouble(-1, 1),
            };

        }while(v.len2() > 1);
        return normalize(v);
    }

    inline mlg::Logger& operator<<(mlg::Logger& out, const Line3f& line)
    {
        return out << "Line3f{ " << line.point() << ", " << line.dir() << '}';
    }
    
    inline mlg::Logger& operator<<(mlg::Logger& out, const Ray3f& line)
    {
        return out << "Ray3f{ " << line.point() << ", " << line.dir() << '}';
    }


}

#endif /* MGEOMERTY_GEOMETRY_HPP */
