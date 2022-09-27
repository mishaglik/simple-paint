cmake_minimum_required(VERSION 3.10)

set (RAY_SOURCES
    RenderSphere.cpp
    Raytracer.cpp
    RenderPlane.cpp
    MaterialCollection.cpp
)

set (RAY_HEADERS
    RenderSphere.hpp
    Raytracer.hpp
    RenderObject.hpp
    RenderPlane.hpp
)

add_library(Raytracer ${RAY_SOURCES} ${RAY_HEADERS})

target_link_libraries(Raytracer PRIVATE AbstractGL MGeomerty LogUtils)

target_include_directories(Raytracer PUBLIC "../")
