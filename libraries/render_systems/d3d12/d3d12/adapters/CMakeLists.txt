target_sources(MorpheusRenderSystemD3D12
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/d3d12_adapter.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/d3d12_adapter.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/d3d12_adapter_list.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/d3d12_adapter_list.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/d3d12_video_mode.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/d3d12_video_mode.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/d3d12_video_mode_list.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/d3d12_video_mode_list.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt"
)

set_source_files_properties(
    "${CMAKE_CURRENT_LIST_DIR}/CMakeList.txt"
    PROPERTIES
        HEADER_FILE_ONLY TRUE # Since it's just a text file, it doesn't need compiled
)


target_sources(MorpheusRenderSystemD3D12Test
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/d3d12_adapter_list.test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/d3d12_video_mode_list.test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt"
)
