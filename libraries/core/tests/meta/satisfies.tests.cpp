#include "morpheus/core/meta/concepts/satisfies.hpp"

#include <catch2/catch_all.hpp>

#include <type_traits>

#if (MORPHEUS_COMPILER != MORPHEUS_GNUC_COMPILER) || (MORPHEUS_COMP_VER >= 130000000)

namespace morpheus::meta
{

template <typename T, auto C>
concept RangeOver = std::ranges::range<T> and concepts::Satisfies<std::ranges::range_value_t<T>, C>;

template <typename T>
concept HasRangeOfIds = requires(T t) {
    {
        t.ids()
    } -> RangeOver<[]<std::integral> {}>;
};

/* GCC 12 barfs on use of this technique:

/home/runner/work/Morpheus/Morpheus/libraries/core/tests/meta/satisfies.tests.cpp: In function �void morpheus::meta::CATCH2_INTERNAL_TEST_0()�:
/home/runner/work/Morpheus/Morpheus/libraries/core/tests/meta/satisfies.tests.cpp:16:30: internal compiler error: Segmentation fault
   16 |     { t.ids() } -> RangeOver<[]<std::integral>{}>;
      |                              ^~~~~~~~~~~~~~~~~~~
0x1b3ed3a internal_error(char const*, ...)
    ???:0
0x803268 template_parms_to_args(tree_node*)
    ???:0
0x82e6ce tsubst_lambda_expr(tree_node*, tree_node*, int, tree_node*)
    ???:0
0x813675 tsubst_copy_and_build(tree_node*, tree_node*, int, tree_node*, bool, bool)
    ???:0
0x825d17 tsubst_template_arg(tree_node*, tree_node*, int, tree_node*)
    ???:0
0x6ee2db constraints_satisfied_p(tree_node*, tree_node*)
    ???:0
0x80e7e5 do_auto_deduction(tree_node*, tree_node*, tree_node*, int, auto_deduction_context, tree_node*, int, tree_node*)
    ???:0
0x6ecf4e tsubst_requires_expr(tree_node*, tree_node*, int, tree_node*)
    ???:0
0x812977 tsubst_copy_and_build(tree_node*, tree_node*, int, tree_node*, bool, bool)
    ???:0
0x6ee3a4 evaluate_concept_check(tree_node*)
    ???:0
0x6e138c maybe_constant_value(tree_node*, tree_node*, bool)
    ???:0
0x84e58f finish_static_assert(tree_node*, tree_node*, unsigned int, bool, bool)
    ???:0
0x7fc229 c_parse_file()
    ???:0
0x8e92b5 c_common_parse_file()
    ???:0
*/

TEST_CASE("Meta is string allows the compile time detection of string types", "[morpheus.meta.concepts.satisfies]")
{
    SECTION("std::is_aggregate Test")
    {
        struct RangeOfIds
        {
            std::vector<int> mIds;

            auto ids() const { return mIds; }
        };

        STATIC_REQUIRE(HasRangeOfIds<RangeOfIds>);
    }
}

} // namespace morpheus::meta

#endif // #if (MORPHEUS_COMPILER != MORPHEUS_GNUC_COMPILER) || (MORPHEUS_COMP_VER >= 130000000)
