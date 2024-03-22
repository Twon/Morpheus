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
    RESULT DATE_SUPPORTED
    MSVC_VERSION "19.26"
    GNU_VERSION "14"
)

morpheus_conformance_check(
    RESULT EXPECTED_SUPPORTED
    MSVC_VERSION "19.33"
    GNU_VERSION "12"
    CLANG_VERSION "16"
    APPLECLANG_VERSION "15"
)

morpheus_conformance_check(
    RESULT FORMAT_SUPPORTED
    MSVC_VERSION "19.29"
    GNU_VERSION "13"
    CLANG_VERSION "17"
    APPLECLANG_VERSION "15"
)

if (NOT ${DATE_SUPPORTED})
    find_package(date REQUIRED)
endif (NOT ${DATE_SUPPORTED})

if (NOT ${EXPECTED_SUPPORTED})
    find_package(tl-expected REQUIRED)
endif (NOT ${EXPECTED_SUPPORTED})

if (NOT ${FORMAT_SUPPORTED})
    find_package(fmt REQUIRED)
endif (NOT ${FORMAT_SUPPORTED})

find_package(range-v3 REQUIRED)
find_package(scn REQUIRED)


target_link_libraries(MorpheusCore
    PUBLIC
        $<$<NOT:$<BOOL:${DATE_SUPPORTED}>>:date::date>
        $<$<NOT:$<BOOL:${DATE_SUPPORTED}>>:date::date-tz>
        $<$<NOT:$<BOOL:${DATE_SUPPORTED}>>:fmt::fmt>
        range-v3::range-v3
        scn::scn
        $<$<NOT:$<BOOL:${EXPECTED_SUPPORTED}>>:tl::expected>
)

target_compile_definitions(MorpheusCore
    PUBLIC
        $<$<PLATFORM_ID:Darwin>:_GNU_SOURCE=1> # Boost stacktrace requires this for MacOS.
)
