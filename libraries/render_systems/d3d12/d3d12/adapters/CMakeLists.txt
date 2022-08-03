target_sources(MorpheusRenderSystemD3D12
    PRIVATE
        adapter.hpp
        adapter.cpp
        adapter_list.hpp
        adapter_list.cpp
        video_mode.hpp
        video_mode.cpp
        video_mode_list.hpp
        video_mode_list.cpp
)

target_sources(MorpheusRenderSystemD3D12Test
    PRIVATE
        adapter_list.tests.cpp
        video_mode_list.tests.cpp
)
