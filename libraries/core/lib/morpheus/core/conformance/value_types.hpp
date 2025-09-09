#pragma once

#include <morpheus/core/conformance/version.hpp>

// clang-format off
#if (__cpp_lib_indirect >= 202502L) && (__cpp_lib_polymorphic >= 202502L)
    #include <memory> // IWYU pragma: export
    namespace morpheus::conf { namespace vt = ::std; }
#else
    #include <indirect.h> // IWYU pragma: export
    #include <polymorphic.h> // IWYU pragma: export
    namespace morpheus::conf { namespace vt = ::xyz; }
#endif
// clang-format on
