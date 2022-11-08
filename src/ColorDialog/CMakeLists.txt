cmake_minimum_required(VERSION 3.10)

set (COLDIALOG_SOURCES
    ColorDialog.cpp
    )

set (COLDIALOG_HEADERS
    ColorDialog.cpp    
)

add_library(ColorDialog ${COLDIALOG_SOURCES} ${COLDIALOG_HEADERS})

target_link_libraries(ColorDialog PRIVATE AbstractGL MGeomerty LogUtils Widgets)

target_include_directories(ColorDialog PUBLIC "../")
