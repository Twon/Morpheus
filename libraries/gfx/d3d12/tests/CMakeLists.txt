morpheus_add_tests(
    NAME MorpheusGfxD3D12Tests
    FOLDER "Libraries/Gfx/D3D12"
    LABELS GPU
)

target_link_libraries(MorpheusGfxD3D12Tests
    PRIVATE
        morpheus::gfx::d3d12
)

target_sources(MorpheusGfxD3D12Tests
    PRIVATE
        adapter.tests.cpp
        video_mode_list.tests.cpp
)
