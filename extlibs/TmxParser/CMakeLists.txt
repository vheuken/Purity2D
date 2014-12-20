cmake_minimum_required(VERSION 2.8)
project(tmxparser)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
message("Configuring tmxparser version ${VERSION}")

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/src/*.h)
set(miniz ${PROJECT_SOURCE_DIR}/src/miniz.c)

set(LIB_CFLAGS "-pedantic -Werror -Wall -Werror=strict-prototypes -Werror=old-style-definition -Werror=missing-prototypes")
set(EXAMPLE_CFLAGS "-pedantic -Werror -Wall")
#include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(tmxparser_static STATIC ${SOURCES} ${HEADERS} ${miniz})
target_link_libraries(tmxparser_static tinyxml2static)
