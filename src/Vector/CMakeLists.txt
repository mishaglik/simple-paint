cmake_minimum_required(VERSION 3.10)

set (VECTOR_SOURCES
    Vector.cpp
)

set (VECTOR_HEADERS
    Vector.hpp
)

add_library(Vector ${VECTOR_SOURCES} ${VECTOR_HEADERS})

target_link_libraries(Vector LogUtils)
# target_include_directories(Vector PUBLIC "${PROJECT_SOURCE_DIR}/src")
