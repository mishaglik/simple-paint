cmake_minimum_required(VERSION 3.10)

# add_library(Base MODULE Base.cpp)
add_library(Pen MODULE Pen.cpp Interpolate.cpp Vector.cpp BBrushes.cpp Color.cpp)
add_library(ShapeFillers MODULE ShapeFillers.cpp)
add_library(Pippet MODULE Pippet.cpp)
add_library(Grayer MODULE Grayer.cpp)
add_library(Filler MODULE Filler.cpp Vector.cpp Color.cpp)

set (Plugins
    Pen
    ShapeFillers
    Pippet
    Grayer
    Filler
)

foreach(Plugin ${Plugins})
add_custom_command(TARGET ${Plugin} POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different      # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/build/src/Plugins/lib${Plugin}.so"    # <--this is in-file
        "${PROJECT_SOURCE_DIR}/modules/${Plugin}.aboba.so") 
target_compile_definitions(${Plugin} PUBLIC PLUGIN)
# target_link_libraries(${Plugin} PRIVATE MGeomerty)
endforeach()