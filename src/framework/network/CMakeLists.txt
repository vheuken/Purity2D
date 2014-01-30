set(NETWORK_PROJECT_NAME "Purity-Network")

project(${NETWORK_PROJECT_NAME})

set( NETWORK_HEADER_FILES
     host.h
     client.h
     server.h
     networkaction.h
)

set( NETWORK_SOURCE_FILES
     host.cpp
     client.cpp
     server.cpp
)

add_library( ${NETWORK_PROJECT_NAME} STATIC
             ${NETWORK_HEADER_FILES}
             ${NETWORK_SOURCE_FILES}
)

target_link_libraries( ${NETWORK_PROJECT_NAME}
                       enet
)