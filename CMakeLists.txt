cmake_minimum_required(VERSION 3.10)

project(Vecplot VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED True)

set(VP_SOURCE_DIR
    src
)

set(VP_SOURCES
    ${VP_SOURCE_DIR}/main.cpp
    ${VP_SOURCE_DIR}/CoordinateSystem.cpp
    ${VP_SOURCE_DIR}/VectorPlot.cpp
    ${VP_SOURCE_DIR}/Application.cpp
    ${VP_SOURCE_DIR}/Raycaster.cpp
)

set(VP_LIBS
    MGeomerty
    AbstractGL
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -Wno-error=padded)
endif()

foreach(lib ${VP_LIBS})
    add_subdirectory(${VP_SOURCE_DIR}/${lib})
endforeach()

add_executable(main ${VP_SOURCES})

target_link_libraries(main PUBLIC ${VP_LIBS})

# target_include_directories(main PUBLIC 
    # ${VP_SOURCE_DIR}/MGeomerty
# )