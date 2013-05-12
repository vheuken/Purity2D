cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "Oathseeker Engine")

project(${PROJECT_NAME})

message("${BUILD_SETTING}")

# include directories
set(LIBS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libs")

include_directories( 
	${LIBS_INCLUDE_DIR}
)

add_subdirectory(libs)
add_subdirectory(src)