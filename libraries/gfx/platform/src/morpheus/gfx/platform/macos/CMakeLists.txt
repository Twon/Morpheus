target_sources(MorpheusGfxPlatform
    PUBLIC
        FILE_SET HEADERS
        FILES
            application_delegate.h
            render_window.hpp
            window_delegate.h
    PRIVATE
        application_delegate.mm
        render_window.mm
        window_delegate.mm
)

target_link_libraries(MorpheusGfxPlatform
    PUBLIC
        "-framework Foundation"
        "-framework Cocoa"
)
