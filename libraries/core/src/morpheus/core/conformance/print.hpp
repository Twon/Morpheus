#pragma once

#include <morpheus/core/conformance/version.hpp>

#if __has_include(<print>)
    #include <print> // IWYU pragma: export
#endif // #if __has_include(<print>)

// clang-format off
#if (__cpp_lib_print >= 202207L)
    namespace morpheus { namespace print_ns = std; }
#else
    #include <fmt/core.h> // IWYU pragma: export
    namespace morpheus { namespace print_ns = fmt; }
#endif
// clang-format on
