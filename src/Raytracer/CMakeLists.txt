cmake_minimum_required(VERSION 3.10)

set (RAY_SOURCES
    RenderSphere.cpp
    Raytracer.cpp
)

add_library(Raytracer ${RAY_SOURCES})

target_link_libraries(Raytracer PRIVATE AbstractGL MGeomerty)

target_include_directories(Raytracer PUBLIC "../")
