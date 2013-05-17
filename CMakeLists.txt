cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "Purity Engine")

project(${PROJECT_NAME})


# include directories
set(LIBS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libs")

include_directories( 
	${LIBS_INCLUDE_DIR}
    ${LIBS_INCLUDE_DIR}/SFML-2.0/include/
)

add_subdirectory(libs PRE_BUILD)
add_subdirectory(src)
