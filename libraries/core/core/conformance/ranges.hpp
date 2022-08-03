#pragma once

#include <version>

#if __has_include(<ranges>)
#include <ranges>
#endif

#include <iterator>




#if (__cpp_lib_ranges >= 202202L)

namespace morpheus
{

namespace ranges {

using std::ranges::begin;
using std::ranges::end;
using std::ranges::distance;

using std::ranges::back_inserter;
using std::ranges::input_range;
using std::ranges::move;
using std::ranges::iterator_t;
using std::ranges::range_value_t;

using std::ranges::lower_bound;
using std::ranges::transform;

}

} // namespace morpheus

#else

#include <range/v3/algorithm/lower_bound.hpp>
#include <range/v3/algorithm/move.hpp>
#include <range/v3/algorithm/transform.hpp>
//#include <range/v3/functional/comparisons.hpp>
//#include <range/v3/iterator.hpp>
//#include <range/v3/iterator/concepts.hpp>
#include <range/v3/iterator/insert_iterators.hpp>
//#include <range/v3/range/concepts.hpp>

namespace morpheus
{

namespace ranges {

using ::ranges::begin;
using ::ranges::end;
using ::ranges::distance;

using ::ranges::back_inserter;
using ::ranges::input_range;
using ::ranges::move;
using ::ranges::iterator_t;
using ::ranges::range_value_t;

using ::ranges::lower_bound;
using ::ranges::transform;

}

} // namespace morpheus

#endif
