target_sources(MorpheusCore
    PUBLIC
        FILE_SET HEADERS
        FILES
            architecture.hpp
            assert.hpp
            assert_handler.hpp
            cold.hpp
            compiler.hpp
            debugging.hpp
            exceptions.hpp
            platform.hpp
            prerequisites.hpp
            sanitizers.hpp
            scoped_action.hpp
            verify.hpp
    PRIVATE
        assert_handler.cpp
        debugging.cpp
        exceptions.cpp
)

target_link_libraries(MorpheusCore
    PRIVATE
        Boost::unit_test_framework
)
