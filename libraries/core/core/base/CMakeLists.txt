target_sources(MorpheusCore
    PUBLIC
        assert.hpp
        compiler.hpp
        debugging.hpp
        sanitizers.hpp
        unreachable.hpp
        verify.hpp
    PRIVATE
        assert.cpp
        debugging.cpp
)

target_link_libraries(MorpheusCore
    PUBLIC
        Boost::headers
)

target_sources(MorpheusCoreTests
    PRIVATE
        assert.tests.cpp
        verify.tests.cpp
)

