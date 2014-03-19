project(${PROJECT_NAME})

if (UNIX)
    SET(CMAKE_CXX_FLAGS "-std=c++11")
endif()

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

include_directories( 
    ${LIBS_INCLUDE_DIR}
    ${LIBS_INCLUDE_DIR}/lua-5.2.2/src
    ${LIBS_INCLUDE_DIR}/luabind/
    ${LIBS_INCLUDE_DIR}/enet/include
    ${LIBS_INCLUDE_DIR}/SDL2-2.0.1/include
    ${LIBS_INCLUDE_DIR}/SDL2_image-2.0.0/
)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE( Boost COMPONENTS filesystem system REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_subdirectory(framework)
add_subdirectory(engine)
