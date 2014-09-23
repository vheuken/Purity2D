set(SYSTEM_PROJECT_NAME "Purity-System")

project(${SYSTEM_PROJECT_NAME})

set( SYSTEM_HEADER_FILES
     vector2.h
     timer.h
     event.h
     configuration.h
     actionmanager.h
)

set( SYSTEM_SOURCE_FILES     
     vector2.inl
     timer.cpp
     event.cpp
     configuration.cpp
     actionmanager.cpp
)

add_library( ${SYSTEM_PROJECT_NAME} STATIC 
             ${SYSTEM_HEADER_FILES}
             ${SYSTEM_SOURCE_FILES}
)

SET_TARGET_PROPERTIES(${SYSTEM_PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${SYSTEM_PROJECT_NAME} inih)
