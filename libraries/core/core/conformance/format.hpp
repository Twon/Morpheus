#pragma once

#if __has_include(<format>)
#   include <format>
namespace morpheus { namespace fmt_ns = std; }
#else
#   include <fmt/format.h>
#   include <fmt/ostream.h>
namespace morpheus { namespace fmt_ns = fmt; }
#endif
