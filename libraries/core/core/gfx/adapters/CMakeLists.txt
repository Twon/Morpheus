target_sources(MorpheusCore
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/adapter.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/adapter.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/adapter_list.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/adapter_list.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/video_mode.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/video_mode.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/video_mode_list.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/video_mode_list.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt"
)

set_source_files_properties(
    "${CMAKE_CURRENT_LIST_DIR}/CMakeList.txt"
    PROPERTIES
        HEADER_FILE_ONLY TRUE # Since it's just a text file, it doesn't need compiled
)


target_sources(MorpheusCoreTests
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/adapter_list.test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/video_mode_list.test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt"
)
