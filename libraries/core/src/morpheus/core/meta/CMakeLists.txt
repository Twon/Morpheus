target_sources(MorpheusCore
    PUBLIC
        aggregate.hpp
        binary_search.hpp
        complete.hpp
        is_specialisation.hpp
        is_string.hpp
)

add_subdirectory(concepts)
add_subdirectory(detail)