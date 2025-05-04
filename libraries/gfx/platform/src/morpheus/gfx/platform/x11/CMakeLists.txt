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

find_package(X11 REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(XRANDR REQUIRED xrandr)

target_link_libraries(MorpheusGfxPlatform
    PRIVATE
        X11
        Xrandr
)