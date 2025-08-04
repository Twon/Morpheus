#include <morpheus/core/conformance/version.hpp>

#include <catch2/catch_test_macros.hpp>

#include <compare>

namespace morpheus
{

TEST_CASE("Explicitly check compiler feature flags requirements for language features", "[morpheus.base.compilers.features.language]")
{
    STATIC_REQUIRE(__cpp_attributes >= 200809L); // attribute support.
    //STATIC_REQUIRE(__cpp_consteval >= 201811L); // consteval support - immediate functions.
    STATIC_REQUIRE(__cpp_deduction_guides >= 201703L); // CTAD for class templates.
#if defined(__cpp_lib_three_way_comparison)
    STATIC_REQUIRE(__cpp_lib_three_way_comparison >= 201907L); // Spaceship operator support.
#endif // #if defined(__cpp_lib_three_way_comparison)
}

TEST_CASE("Explicitly check compiler feature flags requirements for library features", "[morpheus.base.compilers.features.library]")
{
    STATIC_REQUIRE(__cpp_lib_adaptor_iterator_pair_constructor >= 202106L); // Iterator pair constructors for std::stack and std::queue.
    STATIC_REQUIRE(__cpp_lib_chrono >= 201611L); // Constexpr support for std::chrono::duration and std::chrono::time_point.
    //STATIC_REQUIRE(__cpp_lib_expected >= 202202L); // std::expected supports monadic operations.
    STATIC_REQUIRE(__cpp_lib_exchange_function >= 201304L); // std::exchange()
    STATIC_REQUIRE(__cpp_lib_filesystem >= 201703L); // std::filesystem library.
    STATIC_REQUIRE(__cpp_lib_optional >= 201606L); // std::optional.
    STATIC_REQUIRE(__cpp_lib_string_view >= 201606L); // std::string_view.
    STATIC_REQUIRE(__cpp_lib_span >= 202002L); // std::span.
}

} // namespace morpheus
