target_sources(MorpheusRenderSystemGL4
    PUBLIC
        adapter.hpp
        video_mode.hpp
    PRIVATE
        adapter.cpp
        video_mode.cpp
)

target_sources(MorpheusRenderSystemGL4Tests
    PRIVATE
        adapter.tests.cpp
        video_mode.tests.cpp
)