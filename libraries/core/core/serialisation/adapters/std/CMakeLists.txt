target_sources(MorpheusCore
    PUBLIC
        optional.hpp
        pair.hpp
        tuple.hpp
        variant.hpp
)

target_sources(MorpheusCoreTests
    PRIVATE
        optional.tests.cpp
        pair.tests.cpp
        tuple.tests.cpp
        variant.tests.cpp
)
