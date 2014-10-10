set(WINDOW_PROJECT_NAME "Purity-Window")

project(${WINDOW_PROJECT_NAME})

if (WIN32)
	set(PLATFORM_HEADER_FILES
	    win32/window.h
		)
	set(PLATFORM_SOURCE_FILES
	    win32/window.cpp
		)
endif(WIN32)

set( WINDOW_HEADER_FILES
     window.h
     windowmanipulator.h
	 ${PLATFORM_HEADER_FILES}
)

set( WINDOW_SOURCE_FILES
     window.cpp
     windowmanipulator.cpp
	 ${PLATFORM_SOURCE_FILES}
)

add_library( ${WINDOW_PROJECT_NAME} STATIC
             ${WINDOW_HEADER_FILES}
             ${WINDOW_SOURCE_FILES}
)

target_link_libraries ( ${WINDOW_PROJECT_NAME}
                        SDL2-static
)
