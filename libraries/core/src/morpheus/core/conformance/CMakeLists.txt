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

morpheus_conformance_check(
    RESULT DATE_FALLBACK
    MSVC_VERSION "19.26"
    GCC_VERSION "14"
)

morpheus_conformance_check(
    RESULT EXPECTED_FALLBACK
    MSVC_VERSION "19.33"
    GCC_VERSION "12"
    CLANG_VERSION "16"
    APPLECLANG_VERSION "15"
)

message(STATUS "DATE_FALLBACK: ${DATE_FALLBACK}")
message(STATUS "EXPECTED_FALLBACK: ${EXPECTED_FALLBACK}")

if (${DATE_FALLBACK})
    message(STATUS "find_package date")
    find_package(date REQUIRED)
endif (${DATE_FALLBACK})

if (${EXPECTED_FALLBACK})
    message(STATUS "find_package tl-expected")
    find_package(tl-expected REQUIRED)
endif (${EXPECTED_FALLBACK})

find_package(fmt REQUIRED)
find_package(range-v3 REQUIRED)
find_package(scn REQUIRED)


target_link_libraries(MorpheusCore
    PUBLIC
        $<$<BOOL:${DATE_FALLBACK}>:date::date> # Only Visual Studio 19.26 onwards has a complete implementation: https://en.cppreference.com/w/cpp/compiler_support
        $<$<BOOL:${DATE_FALLBACK}>:date::date-tz>
        fmt::fmt
        range-v3::range-v3
        scn::scn
        $<$<BOOL:${EXPECTED_FALLBACK}>:tl::expected>
)

target_compile_definitions(MorpheusCore
    PUBLIC
        $<$<PLATFORM_ID:Darwin>:_GNU_SOURCE=1> # Boost stacktrace requires this for MacOS.
)
