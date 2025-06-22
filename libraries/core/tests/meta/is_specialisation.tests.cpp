
#include "morpheus/core/meta/is_specialisation.hpp"

#include <catch2/catch_test_macros.hpp>

#include <complex>
#include <list>
#include <optional>
#include <set>
#include <tuple>
#include <unordered_set>
#include <vector>


namespace morpheus::meta
{

template <typename T>
class TestTemplateWith1Param {};

template <typename T1, typename T2>
class TestTemplateWith2Param {};

template <typename T>
inline constexpr bool isVector = meta::IsSpecialisationOf<std::vector, T>;

TEST_CASE("Meta is specialisation allows the compile time detection of specialisations", "[morpheus.meta.is_specialisation]")
{
    SECTION("Test against simple types")
    {
        STATIC_REQUIRE(meta::is_specialisation_of_v<TestTemplateWith1Param, TestTemplateWith1Param<int>>);
        STATIC_REQUIRE(meta::is_specialisation_of_v<TestTemplateWith2Param, TestTemplateWith2Param<int, int>>);
    }
    SECTION("Test against STL types")
    {
        // 1 arg templates
        STATIC_REQUIRE(meta::is_specialisation_of_v<std::complex, std::complex<int>>);
        STATIC_REQUIRE(meta::is_specialisation_of_v<std::list, std::list<int>>);
        STATIC_REQUIRE(meta::is_specialisation_of_v<std::optional, std::optional<int>>);
        STATIC_REQUIRE(meta::is_specialisation_of_v<std::set, std::set<int>>);
        STATIC_REQUIRE(meta::is_specialisation_of_v<std::vector, std::vector<int>>);
        STATIC_REQUIRE(!meta::is_specialisation_of_v<std::complex, std::list<int>>);
        STATIC_REQUIRE(!meta::is_specialisation_of_v<std::list, std::optional<int>>);
        STATIC_REQUIRE(!meta::is_specialisation_of_v<std::optional, std::set<int>>);
        STATIC_REQUIRE(!meta::is_specialisation_of_v<std::set, std::vector<int>>);
        STATIC_REQUIRE(!meta::is_specialisation_of_v<std::vector, std::complex<int>>);

        // 2 arg templates
        STATIC_REQUIRE(meta::is_specialisation_of_v<std::vector, std::vector<int, std::allocator<int>>>);
        STATIC_REQUIRE(!meta::is_specialisation_of_v<std::vector, std::list<int, std::allocator<int>>>);

        // 3 arg templates
        STATIC_REQUIRE(meta::is_specialisation_of_v<std::set, std::set<int, std::less<int>, std::allocator<int>>>);
        STATIC_REQUIRE(!meta::is_specialisation_of_v<std::set, std::tuple<int, std::less<int>, std::allocator<int>>>);

        // 4 arg templates
        STATIC_REQUIRE(meta::is_specialisation_of_v<std::unordered_set, std::unordered_set<int, std::hash<int>, std::equal_to<int>, std::allocator<int>>>);
        STATIC_REQUIRE(!meta::is_specialisation_of_v<std::unordered_set, std::tuple<int, std::hash<int>, std::equal_to<int>, std::allocator<int>>>);
    }
    SECTION("Create specific meta functions based on higher order is_specialisation_of_v function")
    {
        // Meta functions checking for a Is vector works for different instanstitations of vector
        STATIC_REQUIRE(isVector<std::vector<int>>);
        STATIC_REQUIRE(isVector<std::vector<float>>);
        STATIC_REQUIRE(isVector<std::vector<double>>);
        STATIC_REQUIRE(isVector<std::vector<int, std::allocator<int>>>);

        // And detects usage with non vector types.
        STATIC_REQUIRE(!isVector<std::list<int>>);
        STATIC_REQUIRE(!isVector<std::set<int>>);
    }
}

} // namespace morpheus::meta
