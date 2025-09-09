target_sources(MorpheusCore
    PUBLIC
        FILE_SET HEADERS
        FILES
            copier_traits.hpp
            default_copy.hpp
)

add_subdirectory(concepts)
