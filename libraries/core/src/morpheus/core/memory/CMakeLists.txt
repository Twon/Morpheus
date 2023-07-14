target_sources(MorpheusCore
    PUBLIC
        indirect_value.hpp
        polymorphic_value.hpp
)

target_link_libraries(MorpheusCore
    PUBLIC
        polymorphic_value::polymorphic_value
)
