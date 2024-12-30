#pragma once

#include <morpheus/core/conformance/version.hpp>

#if __has_include(<ranges>)
    #include <ranges> // IWYU pragma: export
#endif

// clang-format off
#if (__cpp_lib_ranges >= 202110L)

    #include <algorithm> // IWYU pragma: export
    #include <iterator> // IWYU pragma: export
    namespace morpheus { namespace ranges = std::ranges; }

    namespace std::ranges
    {
        using std::back_inserter; // https://github.com/ericniebler/range-v3/issues/867
    }

#else

    #include <range/v3/algorithm.hpp> // IWYU pragma: export
    #include <range/v3/iterator.hpp> // IWYU pragma: export
    // #include <range/v3/range/concepts.hpp>
    #include <range/v3/range/access.hpp> // IWYU pragma: export
    #include <range/v3/view.hpp> // IWYU pragma: export

    namespace morpheus { namespace ranges = ::ranges; }

#endif // (__cpp_lib_ranges >= 202202L)
// clang-format on
