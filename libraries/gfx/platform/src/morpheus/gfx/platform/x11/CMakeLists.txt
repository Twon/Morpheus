target_sources(MorpheusGfxPlatform
    PUBLIC
        FILE_SET HEADERS
        FILES
            monitor.hpp
            render_window.hpp
    PRIVATE
        monitor.cpp
        render_window.cpp
)
