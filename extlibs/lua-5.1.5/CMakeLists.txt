# Initialize #
##############
SET( TARGET_NAME        "lua" )
SET( TARGET_INCLUDE_DIR "src" )
SET( TARGET_SOURCE_DIR "src" )

if ( (UNIX OR CYGWIN) AND NOT APPLE )
  add_definitions(-DLUA_USE_LINUX)
endif()
if ( APPLE )
  add_definitions(-DLUA_USE_MACOSX)
endif()

SET( HEADER_FILES
	${TARGET_SOURCE_DIR}/lua.h
	${TARGET_SOURCE_DIR}/lualib.h
	${TARGET_SOURCE_DIR}/lauxlib.h
	${TARGET_SOURCE_DIR}/luaconf.h
	${TARGET_SOURCE_DIR}/lua.hpp
)

SET( SOURCE_FILES
	${TARGET_SOURCE_DIR}/lapi.c
	${TARGET_SOURCE_DIR}/lcode.c
	${TARGET_SOURCE_DIR}/ldebug.c
	${TARGET_SOURCE_DIR}/ldo.c
	${TARGET_SOURCE_DIR}/ldump.c
	${TARGET_SOURCE_DIR}/lfunc.c
	${TARGET_SOURCE_DIR}/lgc.c
	${TARGET_SOURCE_DIR}/llex.c
	${TARGET_SOURCE_DIR}/lmem.c
	${TARGET_SOURCE_DIR}/lobject.c
	${TARGET_SOURCE_DIR}/lopcodes.c
	${TARGET_SOURCE_DIR}/lparser.c
	${TARGET_SOURCE_DIR}/lstate.c
	${TARGET_SOURCE_DIR}/lstring.c
	${TARGET_SOURCE_DIR}/ltable.c
	${TARGET_SOURCE_DIR}/ltm.c
	${TARGET_SOURCE_DIR}/lundump.c
	${TARGET_SOURCE_DIR}/lvm.c
	${TARGET_SOURCE_DIR}/lzio.c
	${TARGET_SOURCE_DIR}/lauxlib.c
	${TARGET_SOURCE_DIR}/lbaselib.c
	${TARGET_SOURCE_DIR}/ldblib.c
	${TARGET_SOURCE_DIR}/liolib.c
	${TARGET_SOURCE_DIR}/lmathlib.c
	${TARGET_SOURCE_DIR}/loslib.c
	${TARGET_SOURCE_DIR}/ltablib.c
	${TARGET_SOURCE_DIR}/lstrlib.c
	${TARGET_SOURCE_DIR}/loadlib.c
	${TARGET_SOURCE_DIR}/linit.c


)


INCLUDE_DIRECTORIES( "${TARGET_INCLUDE_DIR}" )

ADD_LIBRARY( "${TARGET_NAME}" STATIC
             ${HEADER_FILES} ${SOURCE_FILES} )



#SET( ${TARGET_NAME}_INCLUDE_DIR "${TARGET_INCLUDE_DIR}" PARENT_SCOPE )

# Disable safety warnings because this is a C library
IF (MSVC)
	ADD_DEFINITIONS(/D _CRT_SECURE_NO_WARNINGS)
ENDIF (MSVC)
