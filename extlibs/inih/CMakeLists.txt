project(inih)
include_directories(../SDL2-2.0.3/include)
add_library(inih STATIC ini.c ini.h cpp/INIReader.cpp cpp/INIReader.h)
