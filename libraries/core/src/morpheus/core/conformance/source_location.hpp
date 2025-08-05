#pragma once

//#if (MORPHEUS_MODULES_SUPPORT)
//    import std;
//#else
    #include <morpheus/core/conformance/version.hpp>
    #if __has_include(<source_location>)
        #include <source_location> // IWYU pragma: export
    #endif
//#endif // #if (MORPHEUS_MODULES_SUPPORT)

// clang-format off
#if (__cpp_lib_source_location >= 201907L)

    namespace morpheus { namespace sl_ns = std; }

    #define MORPHEUS_CURRENT_LOCATION ::morpheus::sl_ns::source_location::current()

#else

    #include <boost/assert/source_location.hpp> // IWYU pragma: export

    namespace morpheus{ namespace sl_ns = boost; }

    #define MORPHEUS_CURRENT_LOCATION BOOST_CURRENT_LOCATION

#endif
// clang-format on
