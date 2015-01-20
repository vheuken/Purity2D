set(PURITY_GUI_PROJECT_NAME "Purity-GUI")
project(${PURITY_GUI_PROJECT_NAME})

set (SOURCE_FILES
     button.cpp
     font.cpp
     text.cpp
)

set (HEADER_FILES
     button.h
     font.h
     text.h
)


add_library(${PURITY_GUI_PROJECT_NAME}
            ${SOURCE_FILES}
            ${HEADER_FILES}
)
