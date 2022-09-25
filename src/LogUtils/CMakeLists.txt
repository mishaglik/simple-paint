cmake_minimum_required(VERSION 3.10)

set (LOGUTILS_SOURCES
    Logger.cpp
    ConsoleLogger.cpp
    LogUtils.cpp
)

set (LOGUTILS_HEADERS
    ConsoleLogger.hpp
    Logger.hpp
    LogUtils.hpp
    NullLogger.hpp
)

add_library(LogUtils ${LOGUTILS_SOURCES} ${LOGUTILS_HEADERS})

target_include_directories(LogUtils PUBLIC "${PROJECT_SOURCE_DIR}/src")
