cmake_minimum_required(VERSION 3.10)

project(Vecplot VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED True)

set(VP_SOURCE_DIR
    src
)

set(VP_SOURCES
    ${VP_SOURCE_DIR}/main.cpp
    ${VP_SOURCE_DIR}/CoordinateSystem.cpp
    ${VP_SOURCE_DIR}/VectorPlot.cpp
    ${VP_SOURCE_DIR}/Application.cpp
    # ${VP_SOURCE_DIR}/Raycaster.cpp
)

set(VP_HEADERS
    ${VP_SOURCE_DIR}/CoordinateSystem.hpp
    ${VP_SOURCE_DIR}/VectorPlot.hpp
    ${VP_SOURCE_DIR}/Application.hpp
    # ${VP_SOURCE_DIR}/Raycaster.hpp
)

set(VP_LIBS
    MGeomerty
    AbstractGL
    Raytracer
    LogUtils
    Vector
    Widgets
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Weverything -O3 -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-weak-vtables)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # add_compile_options(-Wall -Wextra -Wno-error=padded -Wno-weak-vtables)
    set (GNU_SANITIZE_FLAGS
        -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
    )
    add_compile_options(-ggdb3 -O3 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE 
        ${GNU_SANITIZE_FLAGS}
    )
    add_link_options(${GNU_SANITIZE_FLAGS})
endif()

foreach(lib ${VP_LIBS})
    add_subdirectory(${VP_SOURCE_DIR}/${lib})
endforeach()

add_executable(main ${VP_SOURCES} ${VP_HEADERS})

target_link_libraries(main PUBLIC ${VP_LIBS})

# target_include_directories(main PUBLIC 
    # ${VP_SOURCE_DIR}/MGeomerty
# )
