cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "Purity2D")

project(${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
#set(CMAKE_BUILD_TYPE Debug)

set_property( GLOBAL PROPERTY USE_FOLDERS ON)
#ADD_DEFINITIONS("-fPIC")
# include directories
set(LIBS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/extlibs")

include_directories(
    ${LIBS_INCLUDE_DIR}/lua-5.2.2/src
    ${LIBS_INCLUDE_DIR}/LuaBridge/
    ${LIBS_INCLUDE_DIR}/stb_image/
)

if (ANDROID)
    link_directories(C:/android/android-ndk-r10/platforms/android-19/arch-arm/usr/lib/)
    include_directories(
        C:/android/android-ndk-r10/platforms/android-19/arch-arm/usr/include/
    )
endif(ANDROID)

add_subdirectory(extlibs PRE_BUILD)

IF (NOT MSVC)
	# C++11
	ADD_DEFINITIONS(-std=c++11 -Wall)
	
	# statically link libgcc and libstdc++
	if (ANDROID)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --sysroot=C:/android/android-ndk-r10/platforms/android-19/arch-arm/")
    endif()
    IF (NOT APPLE)
	    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")
    endif()
ENDIF (NOT MSVC)

add_subdirectory(src)
