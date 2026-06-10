add_subdirectory(adapters)
add_subdirectory(concepts)

target_sources(MorpheusCore
    PUBLIC
        FILE_SET HEADERS
        FILES
            string.hpp
)
