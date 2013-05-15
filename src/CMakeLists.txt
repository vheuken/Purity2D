project(${PROJECT_NAME})

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

add_definitions(-DSFML_STATIC)

set(SFML_LIBS_PATH "${CMAKE_SOURCE_DIR}/libs/SFML-2.0/lib/Release")

add_executable(${PROJECT_NAME} main.cpp)


target_link_libraries(
	${PROJECT_NAME}

	Box2D
    ${SFML_LIBS_PATH}/sfml-main.lib
    ${SFML_LIBS_PATH}/sfml-system-s.lib
    ${SFML_LIBS_PATH}/sfml-graphics-s.lib
    ${SFML_LIBS_PATH}/sfml-window-s.lib
)
