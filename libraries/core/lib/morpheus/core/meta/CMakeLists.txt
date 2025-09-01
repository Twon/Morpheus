target_sources(MorpheusCore
    PUBLIC
        FILE_SET HEADERS
        FILES
            aggregate.hpp
            binary_search.hpp
            complete.hpp
            is_array.hpp
            is_specialisation.hpp
            is_string.hpp
)

add_subdirectory(concepts)
add_subdirectory(detail)
