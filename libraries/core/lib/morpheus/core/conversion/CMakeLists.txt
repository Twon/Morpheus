add_subdirectory(adapters)

target_sources(MorpheusCore
    PUBLIC
        FILE_SET HEADERS
        FILES
            string.hpp
)
