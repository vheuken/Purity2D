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
)

if (ANDROID)
	add_library( ${ENGINE_PROJECT_NAME} STATIC
					${HEADER_FILES}
					${SOURCE_FILES}
	)
	
	add_library( "main" SHARED 
                 ../../../extlibs/SDL2-2.0.3/src/main/android/SDL_android_main.c
                 main.cpp )

elseif(IOS)
	add_executable( ${ENGINE_PROJECT_NAME} MACOSX_BUNDLE 
					${HEADER_FILES}
					${SOURCE_FILES}
		                        main.cpp
	)
else()
	add_executable( ${ENGINE_PROJECT_NAME} 
					${HEADER_FILES}
					${SOURCE_FILES}
		                        main.cpp
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
	inih	
)

if (ANDROID)
target_link_libraries(
    "main"
    ${ENGINE_PROJECT_NAME}
)
endif(ANDROID)
