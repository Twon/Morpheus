target_sources(MorpheusGfxPlatform
    PUBLIC
        FILE_SET HEADERS
        FILES
            render_window.hpp
    PRIVATE
        render_window.cpp
)

target_link_libraries(MorpheusCore
    PUBLIC
        WIL::WIL
)
