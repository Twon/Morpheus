target_sources(MorpheusGfxVulkan
    PUBLIC
        FILE_SET HEADERS
        FILES
            adapter.hpp
            version.hpp
            video_mode.hpp
            error_codes.hpp
            render_system.hpp
    PRIVATE
        adapter.cpp
        video_mode.cpp
        error_codes.cpp
        render_system.cpp
)
