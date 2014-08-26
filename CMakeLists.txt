cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "Purity2D")

project(${PROJECT_NAME})

if(ANDROID)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
endif(ANDROID)

#set(CMAKE_BUILD_TYPE Debug)

set_property( GLOBAL PROPERTY USE_FOLDERS ON)

# include directories
set(LIBS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/extlibs")

include_directories(
    ${LIBS_INCLUDE_DIR}/lua-5.2.2/src
    ${LIBS_INCLUDE_DIR}/LuaBridge/
    ${LIBS_INCLUDE_DIR}/stb_image/
)

add_subdirectory(extlibs)

IF (NOT MSVC)
	# C++11
	ADD_DEFINITIONS(-std=c++11 -Wall)
	
    IF (NOT APPLE AND NOT ANDROID AND NOT UNIX)
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")
    endif()
ENDIF (NOT MSVC)

add_subdirectory(src)
