target_sources(MorpheusGfxPlatform
    PUBLIC
        FILE_SET HEADERS
        FILES
            error.hpp
            error_codes.hpp
            monitor.hpp
            render_window.hpp
    PRIVATE
        error.cpp
        error_codes.cpp
        monitor.cpp
        render_window.cpp
)

target_link_libraries(MorpheusCore
    PUBLIC
        WIL::WIL
)
