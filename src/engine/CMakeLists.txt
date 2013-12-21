set(ENGINE_PROJECT_NAME "Purity-Engine")

set( HEADER_FILES
    engine.h
    renderer.h
    scenemanager.h
    physicssystem.h
    inputmanager.h
    luamanager.h
    networkmanager.h
)

set( SOURCE_FILES     
     engine.cpp
     renderer.cpp
     scenemanager.cpp
     physicssystem.cpp
     inputmanager.cpp
     luamanager.cpp 
     networkmanager.cpp

     main.cpp
)

add_executable( ${ENGINE_PROJECT_NAME} 
                ${HEADER_FILES}
                ${SOURCE_FILES}
)


target_link_libraries(
    ${ENGINE_PROJECT_NAME}
	
	Purity-Framework
	
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
