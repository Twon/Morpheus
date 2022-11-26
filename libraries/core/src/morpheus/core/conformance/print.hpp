#pragma once

#include <morpheus/core/conformance/version.hpp>

#if __has_include(<print>)
#include <print>
#endif // #if __has_include(<print>)

#if (__cpp_lib_print >= 202207L)
namespace morpheus { namespace print_ns = std; }
#else
#   include <fmt/core.h>
namespace morpheus { namespace print_ns = fmt; }
#endif