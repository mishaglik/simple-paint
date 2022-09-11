cmake_minimum_required(VERSION 3.10)

add_library(MGeomerty Vector.cpp)

target_include_directories(MGeomerty PUBLIC "${PROJECT_SOURCE_DIR}"/src)
