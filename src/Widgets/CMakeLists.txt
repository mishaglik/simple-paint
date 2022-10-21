cmake_minimum_required(VERSION 3.10)

set (AGL_WIDGETS_SOURCES
    Button.cpp
    Widget.cpp
    WindowWidget.cpp
    Menubar.cpp
    Scrollbar.cpp
    TextInput.cpp
    SkinManager.cpp
    Label.cpp
)

set (AGL_WIDGETS_HEADERS
    Button.hpp
    Widget.hpp
    ContainerWidget.hpp
    WindowWidget.hpp
    Menubar.hpp
    Scrollbar.hpp
    TextInput.hpp
    SkinManager.hpp
    Label.hpp
)

find_library(tinyXML2 tinyxml2 PATHS "${PROJECT_SOURCE_DIR}/../libXML")
message("tinyXML: ${tinyXML2}")

add_library(Widgets ${AGL_WIDGETS_SOURCES} ${AGL_WIDGETS_HEADERS})

target_link_libraries(Widgets PUBLIC AbstractGL)
target_link_libraries(Widgets PRIVATE MGeomerty LogUtils)
target_link_libraries(Widgets PRIVATE "${tinyXML2}")


target_include_directories(Widgets PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_include_directories(Widgets PUBLIC "${PROJECT_SOURCE_DIR}/..")
