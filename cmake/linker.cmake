include_guard(GLOBAL)

find_program(MOLD_BIN mold)
if(MOLD_BIN AND (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
    add_link_options("-fuse-ld=mold")
endif()
