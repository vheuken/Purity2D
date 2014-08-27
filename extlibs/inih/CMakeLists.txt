project(inih)
add_library(inih STATIC ini.c ini.h cpp/INIReader.cpp cpp/INIReader.h)
target_link_libraries(inih SDL2-static)