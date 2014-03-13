cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "Purity2D")

project(${PROJECT_NAME})

set(CMAKE_BUILD_TYPE Debug)

set_property( GLOBAL PROPERTY USE_FOLDERS ON)

# include directories
set(LIBS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/extlibs")

include_directories(
    ${LIBS_INCLUDE_DIR}/lua-5.2.2/src    
    ${LIBS_INCLUDE_DIR}/luabind/
)

add_subdirectory(extlibs PRE_BUILD)
add_subdirectory(src)
