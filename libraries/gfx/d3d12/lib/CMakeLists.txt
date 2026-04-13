find_package(D3D12)
if (NOT ${OD3D12_FOUND})
    message("D3D12 not found on the system.  Unable to support D3D12 based render system.")
    return()
endif()

morpheus_add_library(
    NAME MorpheusGfxD3D12
    ALIAS morpheus::gfx::d3d12
    FOLDER "Libraries/Gfx/D3D12"
)

#target_compile_definitions(MorpheusGfxD3D12
#    PUBLIC
#        MORPHEUS_SHARED_BUILD=1
#)

target_include_directories(MorpheusGfxD3D12
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(MorpheusGfxD3D12
	PUBLIC
        morpheus::gfx::platform
        D3D12::DXGI
        D3D12::D3D12
)

set_target_properties(MorpheusGfxD3D12
    PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
)

add_subdirectory(morpheus/gfx/d3d12)
