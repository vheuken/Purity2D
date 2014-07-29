set(ENGINE_PROJECT_NAME "Purity-Engine")

set( HEADER_FILES
    engine.h
    rendersystem.h
    scenemanager.h
    physicssystem.h
    inputmanager.h
    luamanager.h
    networksystem.h
    commandlinearguments.h
    abstractsystem.h
)

set( SOURCE_FILES     
     engine.cpp
     rendersystem.cpp
     scenemanager.cpp
     physicssystem.cpp
     inputmanager.cpp
     luamanager.cpp 
     networksystem.cpp
     commandlinearguments.cpp
     abstractsystem.cpp

     main.cpp
)

if (ANDROID)
	add_library( ${ENGINE_PROJECT_NAME} STATIC
					${HEADER_FILES}
					${SOURCE_FILES}
	)
else()
	add_executable( ${ENGINE_PROJECT_NAME} 
					${HEADER_FILES}
					${SOURCE_FILES}
	)
endif(ANDROID)

target_link_libraries(
    ${ENGINE_PROJECT_NAME}
	
    Purity-Framework
	
    Box2D
    lua
    TMX-Parser
    enet
    STB_Image
	
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
)
