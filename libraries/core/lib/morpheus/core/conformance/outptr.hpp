#pragma once

#include <morpheus/core/conformance/version.hpp>

// clang-format off
#if (__cpp_lib_out_ptr >= 202106L)
    #include <memory> // IWYU pragma: export
    namespace morpheus::conf { namespace ptr = ::std; }
#else
    #include <ztd/out_ptr.hpp> // IWYU pragma: export
    namespace morpheus::conf { namespace ptr = ::ztd::out_ptr; }
#endif
// clang-format on
