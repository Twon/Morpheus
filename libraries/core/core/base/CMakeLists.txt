target_sources(MorpheusCore
    PUBLIC
        assert.hpp
        sanitizers.hpp
        verify.hpp
)

target_sources(MorpheusCoreTests
    PUBLIC
        assert.tests.cpp
        verify.tests.cpp
)

