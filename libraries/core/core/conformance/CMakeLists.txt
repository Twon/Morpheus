target_sources(MorpheusCore
    PUBLIC
        format.hpp
        function_ref.hpp
        print.hpp
        ranges.hpp
        version.hpp
)

target_sources(MorpheusCoreTests
    PRIVATE
        function_ref.tests.cpp
)