#pragma once

#include <core/conformance/version.hpp>

#if __has_include(<ranges>)
#include <ranges>
#endif

#include <iterator>

#if (__cpp_lib_ranges >= 202202L)
namespace morpheus { namespace ranges = std::ranges; }
#else
#include <range/v3/algorithm.hpp>
#include <range/v3/iterator.hpp>
//#include <range/v3/range/concepts.hpp>
#include <range/v3/range/access.hpp>
#include <range/v3/view.hpp>
namespace morpheus { namespace ranges = ::ranges; }
#endif // (__cpp_lib_ranges >= 202202L)
 
