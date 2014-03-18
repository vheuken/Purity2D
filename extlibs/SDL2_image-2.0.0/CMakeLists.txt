cmake_minimum_required(VERSION 2.8)

add_subdirectory(external/libpng-1.6.2)
add_subdirectory(external/jpeg-9)
add_subdirectory(external/tiff-4.0.3)

include_directories(
    ${LIBS_INCLUDE_DIR}/SDL2-2.0.1/include
)

project(SDL2_image)

set(SDL2_IMAGE_SRC
	IMG.c
	IMG_bmp.c
	IMG_gif.c
	IMG_jpg.c
	IMG_lbm.c
	IMG_pcx.c
	IMG_png.c
	IMG_pnm.c
	IMG_tga.c
	IMG_tif.c
	IMG_webp.c
	IMG_xcf.c
	IMG_xpm.c
	IMG_xv.c
	IMG_xxx.c
)

add_definitions(
	-DLOAD_BMP
	-DLOAD_GIF
	-DLOAD_JPG
	-DLOAD_LBM
	-DLOAD_PCX
	-DLOAD_PNG
	-DLOAD_PNM
	-DLOAD_TGA
#	-DLOAD_TIF
#	-DLOAD_WEBP
	-DLOAD_XPM
	-DLOAD_XV
)

add_library(SDL2_image-static STATIC ${SDL2_IMAGE_SRC})

target_link_libraries(SDL2_image-static
	SDL2
	png16_static
#	tiff-static
    jpeg-static
)
