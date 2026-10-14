#pragma once

#include <morpheus/core/base/compiler.hpp>
#include <morpheus/core/conformance/version.hpp>

/// \def MORPHEUS_CPP_LIB_INDIRECT_AND_POLYMORPHIC
///   Gcc 16.0.1 shipped with an initial version of std::indirect before LWG issue 3594 was identified:
///   https://cplusplus.github.io/LWG/issue4325.  This was fixed in 16.1.0. No other compiler has an
///   implementation out before discovery of this issue, so will be unaffected when the support is added.
#define MORPHEUS_CPP_LIB_INDIRECT_AND_POLYMORPHIC ((MORPHEUS_COMPILER == MORPHEUS_GNUC_COMPILER) && (MORPHEUS_COMP_VER >= 160100000))

// clang-format off
#if (__cpp_lib_indirect >= 202502L) && (__cpp_lib_polymorphic >= 202502L) && MORPHEUS_CPP_LIB_INDIRECT_AND_POLYMORPHIC
    #include <memory> // IWYU pragma: export
    namespace morpheus::conf { namespace vt = ::std; }
#else
    #include <indirect.h> // IWYU pragma: export
    #include <polymorphic.h> // IWYU pragma: export
    namespace morpheus::conf { namespace vt = ::xyz; }
#endif
// clang-format on
