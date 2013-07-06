project(${PROJECT_NAME})

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

#add_definitions(-DSFML_STATIC)

#set(SFML_LIBS_PATH "${PROJECT_SOURCE_DIR}/libs/SFML-2.0/lib/Release")
link_directories("${CMAKE_SOURCE_DIR}/PRE_BUILD/SFML-2.0/lib")

FIND_PACKAGE( Boost REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(${PROJECT_NAME} main.cpp)


target_link_libraries(
	${PROJECT_NAME}

	Box2D
    sfml-system
    sfml-graphics
    sfml-window
    lua
    luabind
	${Boost_LIBRARIES}
)
