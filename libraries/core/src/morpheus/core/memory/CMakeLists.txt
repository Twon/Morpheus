target_sources(MorpheusCore
    PUBLIC
        copier_traits.hpp
        default_copy.hpp
        indirect_value.hpp
        polymorphic_value.hpp
)

target_link_libraries(MorpheusCore
    PUBLIC
        polymorphic_value::polymorphic_value
)

add_subdirectory(concepts)