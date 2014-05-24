set(PURITY_GUI_PROJECT_NAME "Purity-GUI")
project(${PURITY_GUI_PROJECT_NAME})

set (SOURCE_FILES
     gui.cpp
)

set (HEADER_FILES
     gui.h
     input.h
)
     

add_library(${PURITY_GUI_PROJECT_NAME}
            ${SOURCE_FILES}
            ${HEADER_FILES}
)