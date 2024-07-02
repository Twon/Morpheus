#pragma once

//#if (MORPHEUS_MODULES_SUPPORT)
//    import std;
//#else
    #if __has_include(<stacktrace>)
        #include <stacktrace>
    #endif
//#endif // #if (MORPHEUS_MODULES_SUPPORT)

// clang-format off
#if (__cpp_lib_stacktrace >= 202011L)

    namespace morpheus { namespace st_ns = std; }

    #define MORPHEUS_CURRENT_STACKTRACE ::morpheus::st_ns::stacktrace::current()
#else

    #include <boost/stacktrace/stacktrace.hpp>
    namespace morpheus { namespace st_ns = boost::stacktrace; }

    #define MORPHEUS_CURRENT_STACKTRACE ::morpheus::st_ns::stacktrace()
#endif
// clang-format on
