#pragma once

#include <core/conformance/version.hpp>

#if __has_include(<format>)
#include <format>
#endif

#if (__cpp_lib_format >= 201907L)
namespace morpheus { namespace fmt_ns = std; }
#else
#   include <fmt/format.h>
#   include <fmt/ostream.h>
namespace morpheus { namespace fmt_ns = fmt; }
#endif
