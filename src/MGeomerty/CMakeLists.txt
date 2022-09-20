cmake_minimum_required(VERSION 3.10)

set (MGEOMETRY_SOURCES
    Intersects.cpp
    Line.cpp
    Rect.cpp
    Sphere.cpp
    Vector.cpp
)

add_library(MGeomerty ${MGEOMETRY_SOURCES})

# target_link_libraries(Raytracer PRIVATE AbstractGL MGeomerty)

target_include_directories(MGeomerty PUBLIC "../")
