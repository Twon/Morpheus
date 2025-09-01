target_sources(MorpheusGfxGL4
    PUBLIC
        FILE_SET HEADERS
        FILES
            prerequisites.hpp
            render_system.hpp
            type_mapping.hpp
    PRIVATE
        render_system.cpp
        type_mapping.cpp
)

if(APPLE)
    add_subdirectory(agl)
endif(APPLE)

if (WIN32)
    add_subdirectory(wgl)
endif(WIN32)

if(UNIX AND NOT APPLE)
    add_subdirectory(xgl)
endif(UNIX AND NOT APPLE)
