target_sources(MorpheusGfxD3D12
    PUBLIC
        FILE_SET HEADERS
        FILES
            adapter.hpp
            render_system.hpp
            type_mapping.hpp
            types.hpp
            verify.hpp
            video_mode.hpp
            video_mode_list.hpp
    PRIVATE
        adapter.cpp
        type_mapping.cpp
        video_mode.cpp
        video_mode_list.cpp
)
