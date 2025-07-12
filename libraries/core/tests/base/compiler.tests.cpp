#include <morpheus/core/conformance/version.hpp>

#include <catch2/catch_test_macros.hpp>



namespace morpheus
{

TEST_CASE("Explicitly check compiler feature flags requirements for language features", "[morpheus.base.compilers.features.language]")
{
    STATIC_REQUIRE(__cpp_attributes >= 200809L); // attribute support.
    STATIC_REQUIRE(__cpp_consteval >= 201811L); // consteval support - immediate functions.
    STATIC_REQUIRE(__cpp_deduction_guides >= 201703L); // CTAD for class templates.
}

TEST_CASE("Explicitly check compiler feature flags requirements for library features", "[morpheus.base.compilers.features.library]")
{
    STATIC_REQUIRE(__cpp_lib_filesystem >= 201703L); // std::filesystem library.
    //STATIC_REQUIRE(__cpp_lib_expected >= 202202L); // std::expected supports monadic operations.
}

} // namespace morpheus
