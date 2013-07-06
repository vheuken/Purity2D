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
	 
	 tinyxml/tinystr.h
	 tinyxml/tinyxml.h
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
	 
	 tinyxml/tinystr.cpp
	 tinyxml/tinyxml.cpp
	 tinyxml/tinyxmlerror.cpp
)

add_library( "${PROJECT_NAME}" STATIC ${HEADER_FILES} ${SOURCE_FILES} )