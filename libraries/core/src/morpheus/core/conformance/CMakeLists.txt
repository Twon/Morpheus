target_sources(MorpheusCore
    PUBLIC
        date.hpp
        format.hpp
        print.hpp
        ranges.hpp
        source_location.hpp
        version.hpp
)

find_package(fmt REQUIRED)
find_package(tl-expected REQUIRED)
find_package(range-v3 REQUIRED)

target_link_libraries(MorpheusCore
    PUBLIC
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:date::date> # Only Visual Studio 19.26 onwards has a complete implementation: https://en.cppreference.com/w/cpp/compiler_support
        fmt::fmt
        range-v3::range-v3
        tl::expected
)