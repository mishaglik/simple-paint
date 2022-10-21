cmake_minimum_required(VERSION 3.10)

set (RAY_SOURCES
    RenderSphere.cpp
    Raytracer.cpp
    RenderPlane.cpp
    MaterialCollection.cpp
    Scene.cpp
    Camera.cpp
    SceneEditor.cpp
)

set (RAY_HEADERS
    RenderSphere.hpp
    Raytracer.hpp
    RenderObject.hpp
    RenderPlane.hpp
    Scene.hpp
    Camera.hpp
    SceneEditor.hpp
)

add_library(Raytracer ${RAY_SOURCES} ${RAY_HEADERS})

target_link_libraries(Raytracer PRIVATE AbstractGL MGeomerty LogUtils)

target_include_directories(Raytracer PUBLIC "../")
