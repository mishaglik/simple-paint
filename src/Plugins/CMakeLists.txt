cmake_minimum_required(VERSION 3.10)

add_library(Base MODULE Base.cpp)

set (Plugins
    Base
)

foreach(Plugin ${Plugins})
add_custom_command(TARGET ${Plugin} POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different      # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/build/src/Plugins/lib${Plugin}.so"    # <--this is in-file
        "${PROJECT_SOURCE_DIR}/modules/${Plugin}.aboba.so") 
target_compile_definitions(${Plugin} PUBLIC PLUGIN)
endforeach()