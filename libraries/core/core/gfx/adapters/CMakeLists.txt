target_sources(MorpheusCore
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

target_sources(MorpheusCoreTests
    PRIVATE
        adapter_list.test.cpp
        video_mode_list.test.cpp
)
