#add_subdirectory(canonical)
add_subdirectory(concepts)
#add_subdirectory(generic)

if(APPLE)
    add_subdirectory(macos)
endif(APPLE)

if(WIN32)
    add_subdirectory(win32)
endif(WIN32)

if(UNIX AND NOT APPLE)
    add_subdirectory(x11)
endif(UNIX AND NOT APPLE)

target_sources(MorpheusGfxPlatform
    PUBLIC
        FILE_SET HEADERS
        FILES
            adapter.hpp
            image.hpp
            monitor.hpp
            pixel.hpp
            render_system.hpp
            render_target.hpp
            render_window.hpp
            vendor.hpp
            video_mode.hpp
    PRIVATE
        adapter.cpp
        image.cpp
        render_system.cpp
        render_target.cpp
        render_window.cpp
        vendor.cpp
        video_mode.cpp
)
