#pragma once

#if __has_include(<stacktrace>)
    #include <stacktrace>
#endif

// clang-format off
#if (__cpp_lib_stacktrace >= 202011L)

    namespace morpheus { namespace st_ns = std; }

    #define MORPHEUS_CURRENT_STACKTRACE ::morpheus::st_ns::stacktrace::current()
#else

    #include <boost/stacktrace/stacktrace.hpp>
    namespace morpheus { namespace st_ns = boost::stacktrace; }

    #define MORPHEUS_CURRENT_STACKTRACE ::morpheus::st_ns::stracktrace()
#endif
// clang-format on