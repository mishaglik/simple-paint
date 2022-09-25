cmake_minimum_required(VERSION 3.10)

set (MGEOMETRY_SOURCES
    Intersects.cpp
    Line.cpp
    Rect.cpp
    Sphere.cpp
    Plane.cpp
    Vector.cpp
)

set (MGEOMETRY_HEADERS
    Intersects.hpp
    Line.hpp
    Rect.hpp
    Sphere.hpp
    Vector.hpp
    Point.hpp
    Geometry.hpp
    Float.hpp
    Plane.hpp
    Operations.hpp
)

add_library(MGeomerty ${MGEOMETRY_SOURCES} ${MGEOMETRY_HEADERS})

target_link_libraries(MGeomerty LogUtils)
target_include_directories(MGeomerty PUBLIC "${PROJECT_SOURCE_DIR}/src")
