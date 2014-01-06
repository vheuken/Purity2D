cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "Purity2D")

project(${PROJECT_NAME})

set_property( GLOBAL PROPERTY USE_FOLDERS ON)

# include directories
set(LIBS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/extlibs")

include_directories( 
    ${LIBS_INCLUDE_DIR}
    ${LIBS_INCLUDE_DIR}/SFML-2.1/include
    ${LIBS_INCLUDE_DIR}/lua-5.2.2/src
    ${LIBS_INCLUDE_DIR}/luabind/
    ${LIBS_INCLUDE_DIR}/enet/include
)

add_subdirectory(extlibs PRE_BUILD)
add_subdirectory(src)
