set(FRAMEWORK_PROJECT_NAME "Purity-Framework")

project(${FRAMEWORK_PROJECT_NAME})

add_subdirectory(network/)

set(MODULES_FOLDER "Purity Framework")

set_target_properties("Purity-Network" PROPERTIES FOLDER ${MODULES_FOLDER})

set( FRAMEWORK_HEADER_FILES
    scene.h
    gamemap.h
    spritesheet.h
    entity.h
    movableentity.h
    texturemanager.h
    entitymanager.h
    tile.h
    layer.h
    entitystate.h
)

set( FRAMEWORK_SOURCE_FILES
     scene.cpp
     gamemap.cpp
     spritesheet.cpp
     entity.cpp
     movableentity.cpp
     texturemanager.cpp
     entitymanager.cpp
     tile.cpp
     layer.cpp
)

add_library( ${FRAMEWORK_PROJECT_NAME} STATIC
             ${FRAMEWORK_HEADER_FILES}
             ${FRAMEWORK_SOURCE_FILES}
)


target_link_libraries(
    ${FRAMEWORK_PROJECT_NAME}
    Purity-Network
)
