project(Guisan)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

include_directories(
    ${LIBS_INCLUDE_DIR}/SDL2-2.0.3/include
    ${LIBS_INCLUDE_DIR}/SDL2_image-2.0.0/
	${CMAKE_CURRENT_SOURCE_DIR}/include
)


file(GLOB headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
     include/*.hpp include/guichan/*.hpp include/guichan/sdl/*.hpp include/guichan/opengl/*.hpp include/guichan/widgets/*.hpp)

file(GLOB sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
     src/*.cpp  src/sdl/*.cpp src/opengl/*.cpp src/widgets/*.cpp)

add_library(Guisan STATIC ${headers} ${sources})
target_link_libraries(Guisan SDL2-static SDL2_image-static)