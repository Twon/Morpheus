target_sources(MorpheusCore
    PUBLIC
        optional.hpp
        pair.hpp
        ranges.hpp
        tuple.hpp
        variant.hpp
)

target_sources(MorpheusCoreTests
    PRIVATE
        optional.tests.cpp
        pair.tests.cpp
        ranges.tests.cpp
        tuple.tests.cpp
        variant.tests.cpp
)
