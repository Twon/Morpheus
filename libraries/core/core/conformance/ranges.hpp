#pragma once

#include <version>

/*#if __has_include(<ranges>)
#include <ranges>
#endif*/


//#if _GLIBCXX_HOSTED
//#error "Poo poo poo"
//#endif

//#ifdef _GLIBCXX_HOSTED
/*#if (__cpp_lib_ranges == 201911L) // !defined(__cpp_lib_ranges) 
#error "Range library and constrained algorithms"
#elif (__cpp_lib_ranges >= 202106L)
#error "Non-default-initialisable views"
#elif (__cpp_lib_ranges >= 202110L)
#error "Views with ownership"
#elif (__cpp_lib_ranges >= 202202L)
#error "std::ranges::range_adaptor_closure"
#else 
#error "All is good in the world"
#endif*/

#if (__cpp_lib_ranges >= 202202L)

namespace morpheus
{

namespace ranges {

using std::ranges::begin;
using std::ranges::end;
using std::ranges::distance;

using std::ranges::input_range;
using std::ranges::range_value_t;

using std::ranges::lower_bound;
using std::ranges::transform;

}

} // namespace morpheus

#else

#include <range/v3/algorithm/lower_bound.hpp>
#include <range/v3/algorithm/move.hpp>
#include <range/v3/algorithm/transform.hpp>
#include <range/v3/functional/comparisons.hpp>
#include <range/v3/iterator.hpp>
#include <range/v3/iterator/concepts.hpp>
#include <range/v3/range/concepts.hpp>

namespace morpheus
{

namespace ranges {

using ::ranges::begin;
using ::ranges::end;
using ::ranges::distance;

using ::ranges::input_range;
using ::ranges::move;
using ::ranges::range_value_t;

using ::ranges::lower_bound;
using ::ranges::transform;

}

} // namespace morpheus

#endif
