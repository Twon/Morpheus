#pragma once

#include <morpheus/core/conformance/version.hpp>

#if __has_include(<format>)
    #include <format>
#endif

#define VALUE_TO_STRING(x) #x
#define VALUE(x) VALUE_TO_STRING(x)
#define PRINT_MACRO_AT_COMPILE_TIME(var) #var "=`" VALUE(var) "`"

#pragma message PRINT_MACRO_AT_COMPILE_TIME(__cpp_lib_format)

// clang-format off
#if (__cpp_lib_format >= 201907L)
    namespace morpheus { namespace fmt_ns = std; }
#else
    #if (MORPHEUS_COMPILER == MORPHEUS_GNUC_COMPILER)
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wstringop-overflow="
    #endif // (MORPHEUS_COMPILER == MORPHEUS_GNUC_COMPILER)

    #include <fmt/format.h>
    #include <fmt/chrono.h>
    #include <fmt/ostream.h>
    namespace morpheus { namespace fmt_ns = fmt; }

    #if (MORPHEUS_COMPILER == MORPHEUS_GNUC_COMPILER)
        #pragma GCC diagnostic pop
    #endif // (MORPHEUS_COMPILER == MORPHEUS_GNUC_COMPILER)
#endif
// clang-format on
