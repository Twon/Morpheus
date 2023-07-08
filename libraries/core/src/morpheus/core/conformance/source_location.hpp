#pragma once

#if __has_include(<source_location>)
    #include <source_location>
#endif

/// \namespace morpheus::sl_ns
///     Conformance namespace abstracting the underlying source_location while compilers do not offer uniform support.
///     When support is missing falls back to boost::source_location.

// clang-format off
#if (__cpp_lib_source_location >= 201907L)

    namespace morpheus { namespace sl_ns = std; }

    #define MORPHEUS_CURRENT_LOCATION ::morpheus::sl_ns::source_location::current()

#else

    #include <boost/assert/source_location.hpp>

    namespace morpheus{ namespace sl_ns = boost; }

    #define MORPHEUS_CURRENT_LOCATION BOOST_CURRENT_LOCATION

#endif
// clang-format on