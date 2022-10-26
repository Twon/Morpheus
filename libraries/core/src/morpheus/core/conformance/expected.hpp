#pragma once

#include <morpheus/core/conformance/version.hpp>

#if __has_include(<expected>)
#include <expected>
#endif

#if (__cpp_lib_expected >= 202202L)
namespace morpheus { namespace exp_ns = std; }
#else
#   include <tl/expected.hpp>
namespace morpheus { namespace exp_ns = tl; }
#endif
