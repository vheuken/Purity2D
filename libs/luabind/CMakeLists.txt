SET(PROJECT_NAME luabind)

# Build and install luabind library ===================================================================================
set( luabind
    "src/class.cpp"
    "src/class_info.cpp"
    "src/class_registry.cpp"
    "src/class_rep.cpp"
    "src/create_class.cpp"
    "src/error.cpp"
    "src/exception_handler.cpp"
    "src/function.cpp"
    "src/inheritance.cpp"
    "src/link_compatibility.cpp"
    "src/object_rep.cpp"
    "src/open.cpp"
    "src/pcall.cpp"
    "src/scope.cpp"
    "src/stack_content_by_name.cpp"
    "src/weak_ref.cpp"
    "src/wrapper_base.cpp"
)
# =====================================================================================================================


# Build ===============================================================================================================
FIND_PACKAGE( Boost REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
add_library( "${PROJECT_NAME}" STATIC ${luabind} )
if( UNIX )
    target_link_libraries( "${PROJECT_NAME}" dl )
endif()
install( TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION "lib"
)