target_sources(MorpheusCore
    PUBLIC
        format.hpp
        function_ref.hpp
        print.hpp
        ranges.hpp
        source_location.hpp
        version.hpp
)

target_sources(MorpheusCoreTests
    PRIVATE
        function_ref.tests.cpp
)

find_package(fmt REQUIRED)
find_package(tl-expected REQUIRED)
find_package(range-v3 REQUIRED)

target_link_libraries(MorpheusCore
    PUBLIC
        fmt::fmt
        range-v3::range-v3
        tl::expected
)