cmake_minimum_required(VERSION 3.10)

set (AGL_SOURCES
    Color.cpp
    EventManager.cpp
    Event.cpp
)

set (AGL_HEADERS
    AWindow.hpp
    AObject.hpp
    AText.hpp
    EventManager.hpp
    Signals.hpp
    Event.hpp
    ATexture.hpp
    ASprite.hpp
    AImage.hpp
)

set (AGL_SFML_SOURCES
    SFMLWindow.cpp
    SFMLText.cpp
    SFMLRenderSurface.cpp
    SFMLTexture.cpp
    SFMLSprite.cpp
    SFMLImage.cpp
)

set (AGL_SFML_HEADERS
    SFMLWindow.cpp
    SFMLText.cpp
    SFMLRenderSurface.cpp
    SFMLTexture.hpp
    SFMLSprite.hpp
    SFMLImage.hpp
)

add_library(AbstractGL ${AGL_SOURCES} ${AGL_HEADERS} ${AGL_SFML_SOURCES} ${AGL_SFML_HEADERS})

target_link_libraries(AbstractGL PRIVATE sfml-graphics sfml-window sfml-system)

target_link_libraries(AbstractGL PRIVATE MGeomerty LogUtils)

target_include_directories(AbstractGL PUBLIC "${PROJECT_SOURCE_DIR}/src")
