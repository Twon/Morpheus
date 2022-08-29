
#include "core/meta/is_specialisation.hpp"

#include <catch2/catch_all.hpp>
#include <array>

namespace morpheus::test
{

template <typename T>
class TestTemplateWith1Param {};

template <typename T1, typename T2>
class TestTemplateWith2Param {};

TEST_CASE("Meta is specialisation allows the compile time detection of specialisations", "[morpheus.meta.is_specialisation]")
{
    static_assert(meta::is_specialisation_of<TestTemplateWith1Param<int>>::value);
    static_assert(meta::is_specialisation_of<TestTemplateWith2Param<int, int>>::value);
    static_assert(meta::is_specialisation_of_v<TestTemplateWith1Param<int>>);
    static_assert(meta::is_specialisation_of_v<TestTemplateWith2Param<int, int>>);
//    static_assert(meta::is_specialisation_of<std::array<int, 5>>::value);
//    static_assert(meta::is_specialisation_of_v<std::array<int, 5>>);
}

} // namespace morpheus::test
