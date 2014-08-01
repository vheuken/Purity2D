project(${PROJECT_NAME})

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

include_directories( 
    ${LIBS_INCLUDE_DIR}
    ${LIBS_INCLUDE_DIR}/lua-5.2.2/src
    ${LIBS_INCLUDE_DIR}/enet/include
    ${LIBS_INCLUDE_DIR}/SDL2-2.0.3/include
    ${LIBS_INCLUDE_DIR}/stb_image/
)

if (WIN32)
	# DirectX
	link_directories($ENV{DXSDK_DIR}/lib/x86)
endif()


add_subdirectory(framework)
add_subdirectory(engine)
