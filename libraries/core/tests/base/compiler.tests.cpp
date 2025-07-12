#include <morpheus/core/conformance/version.hpp>

#include <catch2/catch_test_macros.hpp>



namespace morpheus
{

TEST_CASE("Explicitly check compiler feature flags requirements for language features", "[morpheus.base.compilers.features.language]")
{
    STATIC_REQUIRE(__cpp_consteval >= 201811L); // consteval support - immediate funcions.
}

TEST_CASE("Explicitly check compiler feature flags requirements for library features", "[morpheus.base.compilers.features.library]")
{
    STATIC_REQUIRE(__cpp_lib_filesystem >= 201703L); // std::filesystem library.
    //STATIC_REQUIRE(__cpp_lib_expected >= 202202L); // std::expected supports monadic operations.
}

} // namespace morpheus
