if (WIN32)

add_library(MorpheusRenderSystemD3D12 "")
target_sources(MorpheusRenderSystemD3D12
    PRIVATE
	    "${CMAKE_CURRENT_LIST_DIR}/d3d12_render_system.hpp"
	    "${CMAKE_CURRENT_LIST_DIR}/d3d12_render_system.cpp"
)

target_compile_definitions(MorpheusRenderSystemD3D12
    PUBLIC
	    MORPHEUS_SHARED_BUILD=1
)

target_include_directories(MorpheusCore
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/.."
)

target_link_libraries(MorpheusRenderSystemD3D12
    PRIVATE
	    MorpheusCore
)

set_target_properties(MorpheusRenderSystemD3D12
    PROPERTIES
	     FOLDER "Libraries/RenderSystems"
)

set_target_properties(MorpheusRenderSystemD3D12
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

get_target_property(SOURCES_FILES MorpheusRenderSystemD3D12 SOURCES)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES})

endif()
