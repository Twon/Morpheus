#pragma once

#include <morpheus/core/conformance/version.hpp>

#if __has_include(<ranges>)
    #include <ranges>
#endif

// clang-format off
#if (__cpp_lib_ranges >= 201911L)

    #include <algorithm>
    #include <iterator>
    namespace morpheus { namespace ranges = std::ranges; }

    namespace std::ranges
    {
        using std::back_inserter; // https://github.com/ericniebler/range-v3/issues/867
    }

#else

    #include <range/v3/algorithm.hpp>
    #include <range/v3/iterator.hpp>
    // #include <range/v3/range/concepts.hpp>
    #include <range/v3/range/access.hpp>
    #include <range/v3/view.hpp>

    namespace morpheus { namespace ranges = ::ranges; }

#endif // (__cpp_lib_ranges >= 202202L)
// clang-format on
