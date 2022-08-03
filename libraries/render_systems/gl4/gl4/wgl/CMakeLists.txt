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

target_sources(MorpheusRenderSystemGL4Tests
    PRIVATE
        adapter.tests.cpp
        video_mode.tests.cpp
)