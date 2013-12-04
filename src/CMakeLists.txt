project(${PROJECT_NAME})

if (UNIX)
    SET(CMAKE_CXX_FLAGS "-std=c++11")
endif()

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

add_definitions(-DSFML_STATIC)

#set(SFML_LIBS_PATH "${PROJECT_SOURCE_DIR}/libs/SFML-2.0/lib/Release")
link_directories("${CMAKE_SOURCE_DIR}/PRE_BUILD/SFML-2.1/lib")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE( Boost COMPONENTS filesystem system REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_subdirectory(framework)
add_subdirectory(engine)
