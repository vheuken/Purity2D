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
    engine.h
    scene.h
    gamemap.h
    spritesheet.h
    renderer.h
    scenemanager.h
    physicssystem.h
    inputmanager.h
    luamanager.h
    entity.h
    movableentity.h
    texturemanager.h
	objectmanager.h
    tile.h
)

set( SOURCE_FILES
     engine.cpp
     scene.cpp
     gamemap.cpp
     spritesheet.cpp
     renderer.cpp
     scenemanager.cpp
     physicssystem.cpp
     inputmanager.cpp
     luamanager.cpp
     entity.cpp
     movableentity.cpp
     texturemanager.cpp
	 objectmanager.cpp
     tile.cpp
     
     main.cpp
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
