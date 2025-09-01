target_sources(MorpheusGfxMetal
    PUBLIC
        FILE_SET HEADERS
        FILES
            adapter.hpp
            render_system.hpp
            video_mode.hpp
    PRIVATE
        adapter.cpp
        render_system.mm
        video_mode.cpp
)
