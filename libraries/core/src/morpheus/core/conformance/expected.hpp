#pragma once

#include <morpheus/core/conformance/version.hpp>

#if __has_include(<expected>)
    #include <expected>
#endif

// clang-format off
#if (__cplusplus >= __cpp_lib_expected) && (__cpp_lib_expected >= 202211L)
    namespace morpheus { namespace exp_ns = std; }
#else
    #include <tl/expected.hpp>
    namespace morpheus { namespace exp_ns = tl; }
#endif
// clang-format on
