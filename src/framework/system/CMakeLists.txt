set(SYSTEM_PROJECT_NAME "Purity-System")

project(${SYSTEM_PROJECT_NAME})

set( SYSTEM_HEADER_FILES
     vector2.h
     timer.h
)

set( SYSTEM_SOURCE_FILES     
     vector2.inl
     timer.cpp
)

add_library( ${SYSTEM_PROJECT_NAME} STATIC 
             ${SYSTEM_HEADER_FILES}
             ${SYSTEM_SOURCE_FILES}
)

SET_TARGET_PROPERTIES(${SYSTEM_PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
