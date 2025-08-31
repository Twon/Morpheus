#pragma once

#include <morpheus/core/conformance/version.hpp>

#if __has_include(<source_location>)
    #include <source_location> // IWYU pragma: export
#endif

// clang-format off
#if (__cpp_lib_source_location >= 201907L)

    namespace morpheus::conf { namespace sl = ::std; }

    #define MORPHEUS_CURRENT_LOCATION ::morpheus::conf::sl::source_location::current()

#else

    #include <boost/assert/source_location.hpp> // IWYU pragma: export

    namespace morpheus::conf { namespace sl = ::boost; }

    #define MORPHEUS_CURRENT_LOCATION BOOST_CURRENT_LOCATION

#endif
// clang-format on
