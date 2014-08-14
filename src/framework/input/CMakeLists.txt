set(INPUT_PROJECT_NAME "Purity-Input")

project(${INPUT_PROJECT_NAME})

set( INPUT_HEADER_FILES
     mouse.h
)

set( INPUT_SOURCE_FILES
     mouse.cpp
)

add_library( ${INPUT_PROJECT_NAME} STATIC
             ${INPUT_HEADER_FILES}
             ${INPUT_SOURCE_FILES}
)

if (UNIX AND NOT ANDROID AND NOT APPLE)
    target_link_libraries( ${INPUT_PROJECT_NAME}
                           SDL2-static
			   X11
    )
else()
    target_link_libraries( ${INPUT_PROJECT_NAME}
                           SDL2-static
    )
endif()
