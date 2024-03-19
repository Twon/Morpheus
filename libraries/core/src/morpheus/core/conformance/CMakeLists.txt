target_sources(MorpheusCore
    PUBLIC
        bit_cast.hpp
        coro.hpp
        date.hpp
        format.hpp
        expected.hpp
        print.hpp
        ranges.hpp
        scan.hpp
        source_location.hpp
        stacktrace.hpp
        unreachable.hpp
        version.hpp
)

find_package(fmt REQUIRED)
find_package(range-v3 REQUIRED)
find_package(scn REQUIRED)
find_package(tl-expected REQUIRED)

target_link_libraries(MorpheusCore
    PUBLIC
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:date::date> # Only Visual Studio 19.26 onwards has a complete implementation: https://en.cppreference.com/w/cpp/compiler_support
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:date::date-tz>
        fmt::fmt
        range-v3::range-v3
        scn::scn
        tl::expected
)

target_compile_definitions(MorpheusCore
    PUBLIC
        $<$<PLATFORM_ID:Darwin>:_GNU_SOURCE=1> # Boost stacktrace requires this for MacOS.
)
