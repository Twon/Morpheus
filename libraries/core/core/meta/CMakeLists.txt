target_sources(MorpheusCore
    PUBLIC
        is_specialisation.hpp
        is_string.hpp
)

target_sources(MorpheusCoreTests
    PUBLIC
        is_specialisation.tests.cpp
        is_string.tests.cpp
)

add_subdirectory(concepts)