cmake_minimum_required(VERSION 3.10)

add_library(PluginBase OBJECT Vector.cpp Color.cpp BetPlug.cpp PixArr.cpp)
add_library(Interpol OBJECT BBrushes.cpp Interpolate.cpp BrezLine.cpp)
# add_library(Base MODULE Base.cpp)
add_library(Aero MODULE Aero.cpp Pen.cpp)
add_library(Blur MODULE Blur.cpp Pen.cpp)
add_library(Curve MODULE Curves.cpp)
target_link_libraries(Aero PRIVATE PluginBase Interpol)
target_link_libraries(Blur PRIVATE PluginBase Interpol)
target_link_libraries(Curve PRIVATE PluginBase Interpol)
add_library(ShapeFillers MODULE ShapeFillers.cpp)
add_library(Pippet MODULE Pippet.cpp)
add_library(Grayer MODULE Grayer.cpp)
add_library(Filler MODULE Filler.cpp Vector.cpp Color.cpp)


set (Plugins
    Aero
    ShapeFillers
    Pippet
    Grayer
    Curve
    Blur
    Filler
)

foreach(Plugin ${Plugins})
add_custom_command(TARGET ${Plugin} POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different      # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/build/src/Plugins/lib${Plugin}.so"    # <--this is in-file
        "${PROJECT_SOURCE_DIR}/modules/${Plugin}.aboba.so") 
target_compile_definitions(${Plugin} PUBLIC PLUGIN)
# target_link_libraries(${Plugin} PRIVATE MGeomerty)
# target_link_libraries(${Plugin} PRIVATE Vector)
endforeach()