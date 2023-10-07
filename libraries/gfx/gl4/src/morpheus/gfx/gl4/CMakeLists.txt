target_sources(MorpheusGfxGL4
    PUBLIC
        prerequisites.hpp
        render_system.hpp
        type_mapping.hpp
    PRIVATE
        render_system.cpp
        type_mapping.cpp
)

if (WIN32)
    add_subdirectory(wgl)
endif(WIN32)