set(ENTITY_PROJECT_NAME "Purity-Entity")

project(${ENTITY_PROJECT_NAME})

set( ENTITY_HEADER_FILES
     entity.h
     movableentity.h
     entitystate.h
     entitymanager.h
)

set( ENTITY_SOURCE_FILES
     entity.cpp
     movableentity.cpp
     entitymanager.cpp
)

add_library( ${ENTITY_PROJECT_NAME} STATIC
             ${ENTITY_HEADER_FILES}
             ${ENTITY_SOURCE_FILES}
)

target_link_libraries( ${ENTITY_PROJECT_NAME}
                       Box2D
)
