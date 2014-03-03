project(${PROJECT_NAME})

if (UNIX)
    SET(CMAKE_CXX_FLAGS "-std=c++11")
endif()

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

add_definitions(-DSFML_STATIC)

include_directories( 
    ${LIBS_INCLUDE_DIR}
    ${LIBS_INCLUDE_DIR}/SFML-2.1/include
    ${LIBS_INCLUDE_DIR}/lua-5.2.2/src
    ${LIBS_INCLUDE_DIR}/luabind/
    ${LIBS_INCLUDE_DIR}/enet/include
    ${LIBS_INCLUDE_DIR}/SDL2-2.0.1/include
)

#set(SFML_LIBS_PATH "${PROJECT_SOURCE_DIR}/libs/SFML-2.0/lib/Release")
link_directories("${CMAKE_SOURCE_DIR}/PRE_BUILD/SFML-2.1/lib")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE( Boost COMPONENTS filesystem system REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_subdirectory(framework)
add_subdirectory(engine)
