cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "Oathseeker Engine")

project(${PROJECT_NAME})


# include directories
set(LIBS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libs")

include_directories( 
	${LIBS_INCLUDE_DIR}
    ${LIBS_INCLUDE_DIR}/SFML-2.0/include/
)

set(SFML_LIBS_PATH "${CMAKE_SOURCE_DIR}/libs/SFML-2.0/lib/Release")


add_subdirectory(libs PRE_BUILD)
add_subdirectory(src)

add_dependencies(${PROJECT_NAME} 
    ${SFML_LIBS_PATH}/sfml-main.lib
    ${SFML_LIBS_PATH}/sfml-system-s.lib
    ${SFML_LIBS_PATH}/sfml-graphics-s.lib
    ${SFML_LIBS_PATH}/sfml-window-s.lib)