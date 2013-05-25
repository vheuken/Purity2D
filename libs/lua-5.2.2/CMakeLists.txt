##############
# Initialize #
##############
SET( TARGET_NAME        "lua" )
SET( TARGET_INCLUDE_DIR "src" )
SET( TARGET_SOURCE_DIR "src" )

SET( HEADER_FILES
     "${TARGET_INCLUDE_DIR}/lapi.h"
     "${TARGET_INCLUDE_DIR}/lauxlib.h"
     "${TARGET_INCLUDE_DIR}/lcode.h"
     "${TARGET_INCLUDE_DIR}/lctype.h"
     "${TARGET_INCLUDE_DIR}/ldebug.h"
     "${TARGET_INCLUDE_DIR}/ldo.h"
     "${TARGET_INCLUDE_DIR}/lfunc.h"
     "${TARGET_INCLUDE_DIR}/lgc.h"
     "${TARGET_INCLUDE_DIR}/llex.h"
     "${TARGET_INCLUDE_DIR}/llimits.h"
     "${TARGET_INCLUDE_DIR}/lmem.h"
     "${TARGET_INCLUDE_DIR}/lobject.h"
     "${TARGET_INCLUDE_DIR}/lopcodes.h"
     "${TARGET_INCLUDE_DIR}/lparser.h"
     "${TARGET_INCLUDE_DIR}/lstate.h"
     "${TARGET_INCLUDE_DIR}/lstring.h"
     "${TARGET_INCLUDE_DIR}/ltable.h"
     "${TARGET_INCLUDE_DIR}/ltm.h"
     "${TARGET_INCLUDE_DIR}/lua.h"
     "${TARGET_INCLUDE_DIR}/lua.hpp"
     "${TARGET_INCLUDE_DIR}/luaconf.h"
     "${TARGET_INCLUDE_DIR}/lualib.h"
     "${TARGET_INCLUDE_DIR}/lundump.h"
     "${TARGET_INCLUDE_DIR}/lvm.h"
     "${TARGET_INCLUDE_DIR}/lzio.h" )
SET( SOURCE_FILES
	 "${TARGET_SOURCE_DIR}/lapi.c"
	 "${TARGET_SOURCE_DIR}/lauxlib.c"
	 "${TARGET_SOURCE_DIR}/lbaselib.c"
     "${TARGET_SOURCE_DIR}/lbitlib.c"
	 "${TARGET_SOURCE_DIR}/lcode.c"
     "${TARGET_SOURCE_DIR}/lcorolib.c"
     "${TARGET_SOURCE_DIR}/lctype.c"
	 "${TARGET_SOURCE_DIR}/ldblib.c"
	 "${TARGET_SOURCE_DIR}/ldebug.c"
	 "${TARGET_SOURCE_DIR}/ldo.c"
	 "${TARGET_SOURCE_DIR}/ldump.c"
	 "${TARGET_SOURCE_DIR}/lfunc.c"
	 "${TARGET_SOURCE_DIR}/lgc.c"
	 "${TARGET_SOURCE_DIR}/linit.c"
	 "${TARGET_SOURCE_DIR}/liolib.c"
	 "${TARGET_SOURCE_DIR}/llex.c"
	 "${TARGET_SOURCE_DIR}/lmathlib.c"
	 "${TARGET_SOURCE_DIR}/lmem.c"
	 "${TARGET_SOURCE_DIR}/loadlib.c"
     "${TARGET_SOURCE_DIR}/loadlib_rel.c"
	 "${TARGET_SOURCE_DIR}/lobject.c"
	 "${TARGET_SOURCE_DIR}/lopcodes.c"
	 "${TARGET_SOURCE_DIR}/loslib.c"
	 "${TARGET_SOURCE_DIR}/lparser.c"
	 "${TARGET_SOURCE_DIR}/lstate.c"
	 "${TARGET_SOURCE_DIR}/lstring.c"
	 "${TARGET_SOURCE_DIR}/lstrlib.c"
	 "${TARGET_SOURCE_DIR}/ltable.c"
	 "${TARGET_SOURCE_DIR}/ltablib.c"
	 "${TARGET_SOURCE_DIR}/ltm.c"
	 "${TARGET_SOURCE_DIR}/lundump.c"
	 "${TARGET_SOURCE_DIR}/lvm.c"
	 "${TARGET_SOURCE_DIR}/lzio.c"
     "${TARGET_SOURCE_DIR}/wmain.c"     
     )


INCLUDE_DIRECTORIES( "${TARGET_INCLUDE_DIR}" )

ADD_LIBRARY( "${TARGET_NAME}" STATIC
             ${HEADER_FILES} ${SOURCE_FILES} )

             

#SET( ${TARGET_NAME}_INCLUDE_DIR "${TARGET_INCLUDE_DIR}" PARENT_SCOPE )

# Disable safety warnings because this is a C library
IF (WIN32)
	ADD_DEFINITIONS(/D _CRT_SECURE_NO_WARNINGS)
ENDIF (WIN32)