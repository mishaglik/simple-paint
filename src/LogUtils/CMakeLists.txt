cmake_minimum_required(VERSION 3.10)

set (LOGUTILS_SOURCES
    
)

set (LOGUTILS_HEADERS
    
)

add_library(LogUtils ${LOGUTILS_SOURCES} ${LOGUTILS_HEADERS})

target_include_directories(LogUtils PUBLIC "${PROJECT_SOURCE_DIR}/src")
