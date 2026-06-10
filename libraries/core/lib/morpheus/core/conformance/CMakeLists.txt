target_sources(MorpheusCore
    PUBLIC
        FILE_SET HEADERS
        FILES
            bit_cast.hpp
            coro.hpp
            date.hpp
            format.hpp
            expected.hpp
            outptr.hpp
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
    MSVC_VERSION "19.36"
    GNU_VERSION "13"
    CLANG_VERSION "17"
    APPLECLANG_VERSION "15"
)

# Used for <format> and <print> support, so take the greatest version of both from https://en.cppreference.com/w/cpp/compiler_support
morpheus_conformance_check(
    RESULT FORMAT_SUPPORTED
    MSVC_VERSION "19.37"
    GNU_VERSION "14"
    CLANG_VERSION "19"
)

morpheus_conformance_check(
    RESULT OUTPTR_SUPPORTED
    MSVC_VERSION "19.37"
    GNU_VERSION "14"
    CLANG_VERSION "19"
)

morpheus_conformance_check(
    RESULT RANGES_SUPPORTED
    MSVC_VERSION "19.29"
    GNU_VERSION "10"
    CLANG_VERSION "16"
    APPLECLANG_VERSION "15"
)

morpheus_conformance_check(
    RESULT VALUE_TYPES_SUPPORTED
    GNU_VERSION "16"
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

if (NOT ${OUTPTR_SUPPORTED})
    find_package(out_ptr REQUIRED)
endif (NOT ${OUTPTR_SUPPORTED})

if (NOT ${RANGES_SUPPORTED})
    find_package(range-v3 REQUIRED)
endif (NOT ${RANGES_SUPPORTED})

if (NOT ${VALUE_TYPES_SUPPORTED})
    find_package(value_types REQUIRED)
endif (NOT ${VALUE_TYPES_SUPPORTED})

find_package(scn REQUIRED)

# GCC 12 and later must be compiled with support for stacktrace for it to be usable: https://stackoverflow.com/questions/72341483/how-can-i-generate-a-c23-stacktrace-with-gcc-12-1
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" AND ${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER_EQUAL 12)
    include(CheckCXXSymbolExists)
    check_cxx_symbol_exists(_GLIBCXX_HAVE_STACKTRACE "version" GCC_STACKTRACE_SUPPORTED)
    if(${GCC_STACKTRACE_SUPPORTED})
        message(STATUS "morpheus: GCC version ${CMAKE_CXX_COMPILER_VERSION} is built with support for stacktrace")
    else()
        message(STATUS "morpheus: GCC version ${CMAKE_CXX_COMPILER_VERSION} is not built with support for stacktrace")
    endif()
endif()

target_link_libraries(MorpheusCore
    PUBLIC
        $<$<NOT:$<BOOL:${DATE_SUPPORTED}>>:date::date>
        $<$<NOT:$<BOOL:${DATE_SUPPORTED}>>:date::date-tz>
        $<$<NOT:$<BOOL:${FORMAT_SUPPORTED}>>:fmt::fmt>
        $<$<NOT:$<BOOL:${OUTPTR_SUPPORTED}>>:out_ptr::out_ptr>
        $<$<NOT:$<BOOL:${RANGES_SUPPORTED}>>:range-v3::range-v3>
        $<$<NOT:$<BOOL:${VALUE_TYPES_SUPPORTED}>>:value_types::value_types>
        scn::scn
        $<$<NOT:$<BOOL:${EXPECTED_SUPPORTED}>>:tl::expected>
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<BOOL:${GCC_STACKTRACE_SUPPORTED}>,$<VERSION_GREATER_EQUAL:$<CXX_COMPILER_VERSION>,12>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,14>>:-lstdc++_libbacktrace>
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<BOOL:${GCC_STACKTRACE_SUPPORTED}>,$<VERSION_GREATER_EQUAL:$<CXX_COMPILER_VERSION>,14>>:-lstdc++exp>
)

target_compile_definitions(MorpheusCore
    PUBLIC
        $<$<PLATFORM_ID:Darwin>:_GNU_SOURCE=1> # Boost stacktrace requires this for MacOS.
)
