#pragma once

#include <morpheus/core/conformance/version.hpp>

#if __has_include(<format>)
    #include <format> // IWYU pragma: export
#endif

// clang-format off
#if (__cpp_lib_format >= 201907L)
    namespace morpheus { namespace fmt_ns = std; }
#else
    #if (MORPHEUS_COMPILER == MORPHEUS_GNUC_COMPILER)
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wstringop-overflow="
    #endif // (MORPHEUS_COMPILER == MORPHEUS_GNUC_COMPILER)

    #include <fmt/format.h> // IWYU pragma: export
    #include <fmt/chrono.h> // IWYU pragma: export
    #include <fmt/ostream.h> // IWYU pragma: export
    namespace morpheus { namespace fmt_ns = fmt; }

    #if (MORPHEUS_COMPILER == MORPHEUS_GNUC_COMPILER)
        #pragma GCC diagnostic pop
    #endif // (MORPHEUS_COMPILER == MORPHEUS_GNUC_COMPILER)
#endif
// clang-format on
