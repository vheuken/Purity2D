add_subdirectory(Box2D)
add_subdirectory(lua-5.2.2)
add_subdirectory(TmxParser)
add_subdirectory(enet)
add_subdirectory(SDL2-2.0.3)
add_subdirectory(stb_image)

set(EXTLIBS_FOLDER "External Libraries")

set_target_properties("Box2D" PROPERTIES FOLDER ${EXTLIBS_FOLDER})
set_target_properties("lua" PROPERTIES FOLDER ${EXTLIBS_FOLDER})
set_target_properties("TMX-Parser" PROPERTIES FOLDER ${EXTLIBS_FOLDER})
set_target_properties("enet" PROPERTIES FOLDER ${EXTLIBS_FOLDER})
set_target_properties("SDL2-static" PROPERTIES FOLDER ${EXTLIBS_FOLDER})
