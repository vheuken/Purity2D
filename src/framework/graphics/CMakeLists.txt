set(GRAPHICS_PROJECT_NAME "Purity-Graphics")

project(${GRAPHICS_PROJECT_NAME})

set( GRAPHICS_HEADER_FILES
     drawable.h

     vertex.h
     rendertarget.h
     texture.h
     texturemanager.h
     rect.h
     transformable.h
     view.h
     font.h
)

set( GRAPHICS_SOURCE_FILES
     rendertarget.cpp
     vertex.cpp
     texture.cpp
     texturemanager.cpp
     rect.cpp
     transformable.cpp
     view.cpp
     font.cpp
)

add_library ( ${GRAPHICS_PROJECT_NAME} STATIC
              ${GRAPHICS_HEADER_FILES}
              ${GRAPHICS_SOURCE_FILES}
)


SET_TARGET_PROPERTIES(${GRAPHICS_PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries( ${GRAPHICS_PROJECT_NAME}
                       SDL2-static
                       STB_Image
)
