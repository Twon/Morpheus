target_sources(MorpheusRenderSystemGL4
    PUBLIC
        adapter.hpp
        adapter_list.hpp
        video_mode.hpp
    PRIVATE
        adapter.cpp
        adapter_list.cpp
        video_mode.cpp
)

target_sources(MorpheusRenderSystemGL4Test
    PRIVATE
        adapter.tests.cpp
        video_mode_list.tests.cpp
)