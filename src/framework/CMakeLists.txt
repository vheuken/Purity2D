set(FRAMEWORK_PROJECT_NAME "Purity-Framework")

project(${FRAMEWORK_PROJECT_NAME})

set( FRAMEWORK_HEADER_FILES
    scene.h
    gamemap.h
    spritesheet.h
    entity.h
    movableentity.h
    texturemanager.h
    objectmanager.h
    tile.h
    layer.h
    entitystate.h
    host.h
    server.h
    client.h
)

set( FRAMEWORK_SOURCE_FILES
     scene.cpp
     gamemap.cpp
     spritesheet.cpp
     entity.cpp
     movableentity.cpp
     texturemanager.cpp
     objectmanager.cpp
     tile.cpp
     layer.cpp
     entitystate.cpp
     host.cpp
     server.cpp
     client.cpp
)

add_library( ${FRAMEWORK_PROJECT_NAME} STATIC
             ${FRAMEWORK_HEADER_FILES}
             ${FRAMEWORK_SOURCE_FILES}
)
