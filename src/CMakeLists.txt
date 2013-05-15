project(${PROJECT_NAME})

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

add_definitions(-DSFML_STATIC)

#set(SFML_LIBS_PATH "${PROJECT_SOURCE_DIR}/libs/SFML-2.0/lib/Release")
link_directories("${PROJECT_SOURCE_DIR}/libs/SFML-2.0/lib/Release")

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(
	${PROJECT_NAME}

	Box2D
    sfml-system
    sfml-graphics
    sfml-window
)
