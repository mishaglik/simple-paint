cmake_minimum_required(VERSION 3.10)

add_library(AbstractGL SFMLWindow.cpp Button.cpp Color.cpp Widget.cpp SFMLText.cpp)

target_link_libraries(AbstractGL PRIVATE sfml-graphics sfml-window sfml-system)

target_link_libraries(AbstractGL PRIVATE MGeomerty)

target_include_directories(AbstractGL PUBLIC "../")
