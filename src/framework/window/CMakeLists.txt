set(WINDOW_PROJECT_NAME "Purity-Window")

project(${WINDOW_PROJECT_NAME})

set( WINDOW_HEADER_FILES
     window.h
     windowmanipulator.h
)

set( WINDOW_SOURCE_FILES
     window.cpp
     windowmanipulator.cpp
)

add_library( ${WINDOW_PROJECT_NAME} STATIC
             ${WINDOW_HEADER_FILES}
             ${WINDOW_SOURCE_FILES}
)

target_link_libraries ( ${WINDOW_PROJECT_NAME}
                        SDL2-static
)
