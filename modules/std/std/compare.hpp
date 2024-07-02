/// \file compare.hpp
///     Modularisation for https://eel.is/c++draft/compare.syn
export namespace std
{

// [cmp.categories], comparison category types
using std::partial_ordering;
using std::weak_ordering;
using std::strong_ordering;

// named comparison functions
using std::is_eq;
using std::is_neq;
using std::is_lt;
using std::is_lteq;
using std::is_gt;
using std::is_gteq;

// [cmp.common], common comparison category type
using std::common_comparison_category;
using std::common_comparison_category_t;

// [cmp.concept], concept three_way_comparable
using std::three_way_comparable;
using std::three_way_comparable_with;

// [cmp.result], result of three-way comparison
using std::compare_three_way_result;
using std::compare_three_way_result_t;

// [comparisons.three.way], class compare_three_way
using std::compare_three_way;

// [cmp.alg], comparison algorithms
using std::compare_three_way;

// [cmp.alg], comparison algorithms
/*
inline namespace __cpo
{
    using std::__cpo::strong_order;
    using std::__cpo::weak_order;
    using std::__cpo::partial_order;
    using std::__cpo::compare_strong_order_fallback;
    using std::__cpo::compare_weak_order_fallback;
    using std::__cpo::compare_partial_order_fallback;
} // namespace __cpo
*/

} // namespace std


/*
// all freestanding
namespace std {

  // [comparisons.three.way], class compare_three_way
  struct compare_three_way;

  // [cmp.alg], comparison algorithms
  inline namespace unspecified {
    inline constexpr unspecified strong_order = unspecified;
    inline constexpr unspecified weak_order = unspecified;
    inline constexpr unspecified partial_order = unspecified;
    inline constexpr unspecified compare_strong_order_fallback = unspecified;
    inline constexpr unspecified compare_weak_order_fallback = unspecified;
    inline constexpr unspecified compare_partial_order_fallback = unspecified;
  }
}

*/
