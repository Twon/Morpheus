#pragma once

#include <morpheus/core/conformance/version.hpp>

#if __has_include(<stacktrace>)
    #include <stacktrace> // IWYU pragma: export
#endif

// clang-format off
#if (__cpp_lib_stacktrace >= 202011L)

    namespace morpheus::conf { namespace st = ::std; }

    #define MORPHEUS_CURRENT_STACKTRACE ::morpheus::conf::st::stacktrace::current()
#else

    #include <boost/stacktrace/stacktrace.hpp> // IWYU pragma: export
    namespace morpheus::conf { namespace st = ::boost::stacktrace; }

    #define MORPHEUS_CURRENT_STACKTRACE ::morpheus::conf::st::stacktrace()
#endif
// clang-format on
