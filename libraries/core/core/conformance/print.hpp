#pragma once

#if __has_include(<print>)
#   include <print>
namespace morpheus { namespace print_ns = std; }
#else
#   include <fmt/format.h>
namespace morpheus { namespace print_ns = fmt; }
#endif
