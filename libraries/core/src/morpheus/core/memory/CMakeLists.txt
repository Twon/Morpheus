target_sources(MorpheusCore
    PUBLIC
        copier_traits.hpp
        default_copy.hpp
        indirect_value.hpp
        polymorphic_value.hpp
)

target_sources(MorpheusCoreTests
    PUBLIC
        indirect_value.tests.cpp
        polymorphic_value.tests.cpp
)

add_subdirectory(concepts)