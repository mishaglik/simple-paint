cmake_minimum_required(VERSION 3.10)

set (GEDITOR_SOURCES
    GEditor.cpp
    GEditorWindow.cpp
    Canvas.cpp
    Toolbox.cpp
    BasicTools.cpp
    LeftPanel.cpp
    CentralWidget.cpp
    ColorSelector.cpp
    ToolPanel.cpp
    Plugins.cpp
)
    
set (GEDITOR_HEADERS
    GEditor.hpp
    GEditorWindow.hpp
    Canvas.hpp
    Toolbox.hpp
    BasicTools.hpp
    LeftPanel.hpp
    CentralWidget.hpp
    ColorSelector.hpp
    ToolPanel.hpp
    Plugins.hpp
)

add_library(GEditor ${GEDITOR_SOURCES} ${GEDITOR_HEADERS})

target_link_libraries(GEditor PRIVATE AbstractGL MGeomerty LogUtils Widgets)

target_include_directories(GEditor PUBLIC "../")
