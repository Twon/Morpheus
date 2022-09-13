#pragma once

#include <core/conformance/version.hpp>

#if __has_include(<ranges>)
#include <ranges>
#endif

#if (__cpp_lib_ranges >= 202110L)
#include <iterator>
namespace morpheus { namespace ranges = std::ranges; }

namespace std::ranges
{ 
    using std::back_inserter; // https://github.com/ericniebler/range-v3/issues/867
}

#else
#include <range/v3/algorithm.hpp>
#include <range/v3/iterator.hpp>
//#include <range/v3/range/concepts.hpp>
#include <range/v3/range/access.hpp>
#include <range/v3/view.hpp>
namespace morpheus { namespace ranges = ::ranges; }
#endif // (__cpp_lib_ranges >= 202202L)
 
