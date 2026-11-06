target_sources(MorpheusCore
    PUBLIC
        FILE_SET HEADERS
        FILES
            architecture.hpp
            cold.hpp
            compiler.hpp
            debugging.hpp
            exceptions.hpp
            platform.hpp
            prerequisites.hpp
            sanitizers.hpp
            scoped_action.hpp
    PRIVATE
        debugging.cpp
        exceptions.cpp
)

target_link_libraries(MorpheusCore
    PUBLIC
        libassert::assert
    PRIVATE
        Boost::unit_test_framework
)
