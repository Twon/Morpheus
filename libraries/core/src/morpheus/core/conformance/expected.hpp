#pragma once

#include <morpheus/core/conformance/version.hpp>

#if __has_include(<expected>)
    #include <expected> // IWYU pragma: export
#endif

// clang-format off
#if (__cpp_lib_expected >= 202211L)
    namespace morpheus::conf { namespace exp = ::std; }
#else
    #include <tl/expected.hpp> // IWYU pragma: export
    namespace morpheus::conf { namespace exp = ::tl; }
#endif
// clang-format on
