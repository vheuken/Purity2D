add_subdirectory(SFML-2.1)
add_subdirectory(Box2D)
add_subdirectory(lua-5.2.2)
add_subdirectory(luabind)
add_subdirectory(TmxParser)

set(EXTLIBS_FOLDER "External Libraries")

set_target_properties("Box2D" PROPERTIES FOLDER ${EXTLIBS_FOLDER})
set_target_properties("lua" PROPERTIES FOLDER ${EXTLIBS_FOLDER})
set_target_properties("luabind" PROPERTIES FOLDER ${EXTLIBS_FOLDER})
set_target_properties("TMX-Parser" PROPERTIES FOLDER ${EXTLIBS_FOLDER})