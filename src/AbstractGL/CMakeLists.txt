cmake_minimum_required(VERSION 3.10)

set (AGL_SOURCES
    Button.cpp
    Widget.cpp
    Color.cpp
)

set (AGL_HEADERS
    Button.hpp
    Widget.hpp
    AWindow.hpp
    AObject.hpp
    AText.hpp
)

set (AGL_SFML_SOURCES
    SFMLWindow.cpp
    SFMLText.cpp
    SFMLRenderSurface.cpp
)

set (AGL_SFML_HEADERS
    SFMLWindow.cpp
    SFMLText.cpp
    SFMLRenderSurface.cpp
)

add_library(AbstractGL ${AGL_SOURCES} ${AGL_HEADERS} ${AGL_SFML_SOURCES} ${AGL_SFML_HEADERS})

target_link_libraries(AbstractGL PRIVATE sfml-graphics sfml-window sfml-system)

target_link_libraries(AbstractGL PRIVATE MGeomerty)

target_include_directories(AbstractGL PUBLIC "${PROJECT_SOURCE_DIR}/src")
