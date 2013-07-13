set (PROJECT_NAME "TMX-Parser")
include_directories(tinyxml zlib)
set ( HEADER_FILES
	 Tmx.h
	 TmxEllipse.h
	 TmxImage.h
	 TmxImageLayer.h
	 TmxLayer.h
	 TmxMap.h
	 TmxMapTile.h
	 TmxObject.h
	 TmxObjectGroup.h
	 TmxPoint.h
	 TmxPolygon.h
	 TmxPolyline.h
	 TmxPropertySet.h
	 TmxTile.h
	 TmxTileset.h
	 TmxUtil.h
	 
	 base64/base64.h
)

set ( SOURCE_FILES
	 TmxEllipse.cpp
	 TmxImage.cpp
	 TmxImageLayer.cpp
	 TmxLayer.cpp
	 TmxMap.cpp
	 TmxObject.cpp
	 TmxObjectGroup.cpp
	 TmxPolygon.cpp
	 TmxPolyline.cpp
	 TmxPropertySet.cpp
	 TmxTile.cpp
	 TmxTileset.cpp
	 TmxUtil.cpp
	 
	 base64/base64.cpp
	 
)

file (GLOB zlib_src
	"zlib/*.h" "zlib/*.c"
)

file (GLOB tinyxml_src
	"tinyxml/*.cpp" "tinyxml/*.h"
)

add_library( "${PROJECT_NAME}" STATIC 
${HEADER_FILES} ${SOURCE_FILES} 
${zlib_src}
${tinyxml_src}
)