set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(
	${PROJECT_NAME}

	Box2D
)
