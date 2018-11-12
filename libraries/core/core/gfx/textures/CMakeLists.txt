target_sources(MorpheusCore
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/image.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/image.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt"
)

set_source_files_properties(
    "${CMAKE_CURRENT_LIST_DIR}/CMakeList.txt"
    PROPERTIES
        HEADER_FILE_ONLY TRUE # Since it's just a text file, it doesn't need compiled
)
