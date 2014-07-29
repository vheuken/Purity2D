set(FRAMEWORK_PROJECT_NAME "Purity-Framework")

project(${FRAMEWORK_PROJECT_NAME})

add_subdirectory(network/)
add_subdirectory(entity/)
add_subdirectory(window/)
add_subdirectory(system/)
add_subdirectory(input/)
add_subdirectory(graphics/)

set(MODULES_FOLDER "Purity Framework")

set_target_properties("Purity-Network" PROPERTIES FOLDER ${MODULES_FOLDER})
set_target_properties("Purity-Entity" PROPERTIES FOLDER ${MODULES_FOLDER})
set_target_properties("Purity-Window" PROPERTIES FOLDER ${MODULES_FOLDER})
set_target_properties("Purity-Graphics" PROPERTIES FOLDER ${MODULES_FOLDER})
set_target_properties("Purity-System" PROPERTIES FOLDER ${MODULES_FOLDER})
set_target_properties("Purity-Input" PROPERTIES FOLDER ${MODULES_FOLDER})



set( FRAMEWORK_HEADER_FILES
    scene.h
    gamemap.h
    spritesheet.h
    tile.h
    layer.h
    event.h
)

set( FRAMEWORK_SOURCE_FILES
     scene.cpp
     gamemap.cpp
     spritesheet.cpp
     tile.cpp
     layer.cpp
     event.cpp
)

add_library( ${FRAMEWORK_PROJECT_NAME} STATIC
             ${FRAMEWORK_HEADER_FILES}
             ${FRAMEWORK_SOURCE_FILES}
)


target_link_libraries(
    ${FRAMEWORK_PROJECT_NAME}
    Purity-Network
    Purity-Entity
    Purity-Window
    Purity-System
    Purity-Input
    Purity-Graphics
)
