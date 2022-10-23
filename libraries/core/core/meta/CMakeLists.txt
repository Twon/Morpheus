target_sources(MorpheusCore
    PUBLIC
        complete.hpp
        is_specialisation.hpp
        is_string.hpp
)

target_sources(MorpheusCoreTests
    PUBLIC
        complete.tests.cpp
        is_specialisation.tests.cpp
        is_string.tests.cpp
)

add_subdirectory(concepts)