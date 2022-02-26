add_subdirectory(adapters)
add_subdirectory(textures)
if(WIN32)
    add_subdirectory(win32)
endif(WIN32)

target_sources(MorpheusCore
    PUBLIC
        adapter.hpp
        render_system.hpp
        video_mode.hpp
)