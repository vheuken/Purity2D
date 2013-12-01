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

set( HEADER_FILES
    scene.h
    gamemap.h
    spritesheet.h
    entity.h
    movableentity.h
    texturemanager.h
	objectmanager.h
    tile.h
    layer.h

    engine/engine.h
    engine/renderer.h
    engine/scenemanager.h
    engine/physicssystem.h
    engine/inputmanager.h
    engine/luamanager.h
)

set( SOURCE_FILES
     scene.cpp
     gamemap.cpp
     spritesheet.cpp
     entity.cpp
     movableentity.cpp
     texturemanager.cpp
	 objectmanager.cpp
     tile.cpp
     layer.cpp
     
     engine/engine.cpp
     engine/renderer.cpp
     engine/scenemanager.cpp
     engine/physicssystem.cpp
     engine/inputmanager.cpp
     engine/luamanager.cpp     
     engine/main.cpp
)

add_executable( ${PROJECT_NAME} 
                ${HEADER_FILES}
                ${SOURCE_FILES}
)


target_link_libraries(
    ${PROJECT_NAME}

    Box2D
    sfml-system
    sfml-graphics
    sfml-window
    lua
    luabind
    TMX-Parser
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
)
