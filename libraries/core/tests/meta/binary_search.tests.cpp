#include "morpheus/core/meta/binary_search.hpp"

#include <catch2/catch_all.hpp>

#include <array>
#include <cstdint>

namespace morpheus::meta
{

static constexpr std::array<std::size_t, 10> TestValues = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

template <std::size_t Index, std::size_t Value>
struct FindValueByIndex : std::bool_constant<TestValues[Index] == Value>
{
    static_assert(Index < TestValues.size());
};

template <std::size_t Index>
struct TestPredicate : FindValueByIndex<Index, 7> {};

template <std::size_t Index>
struct TestPredicate2 : std::conditional_t<Index == 7, std::true_type, std::false_type> {};

TEST_CASE("Meta binary_search allows the compile time search of a predicate", "[morpheus.meta.binary_search]")
{
    /*
        STATIC_REQUIRE(meta::FindValueByIndex<0, 0>::value == true);
        STATIC_REQUIRE(meta::FindValueByIndex<0, 1>::value == false);
        STATIC_REQUIRE(meta::FindValueByIndex<0, 2>::value == false);
        STATIC_REQUIRE(meta::FindValueByIndex<0, 3>::value == false);
        STATIC_REQUIRE(meta::FindValueByIndex<0, 4>::value == false);
        STATIC_REQUIRE(meta::FindValueByIndex<0, 5>::value == false);
        STATIC_REQUIRE(meta::FindValueByIndex<0, 6>::value == false);
        STATIC_REQUIRE(meta::FindValueByIndex<0, 7>::value == false);
        STATIC_REQUIRE(meta::FindValueByIndex<0, 8>::value == false);
        STATIC_REQUIRE(meta::FindValueByIndex<0, 9>::value == false);

        STATIC_REQUIRE(meta::FindValueByIndex<1, 0>::value == false);
        STATIC_REQUIRE(meta::FindValueByIndex<1, 1>::value == true);
        STATIC_REQUIRE(meta::FindValueByIndex<1, 2>::value == false);
        STATIC_REQUIRE(meta::FindValueByIndex<1, 3>::value == false);
        STATIC_REQUIRE(meta::FindValueByIndex<1, 4>::value == false);
        STATIC_REQUIRE(meta::FindValueByIndex<1, 5>::value == false);
        STATIC_REQUIRE(meta::FindValueByIndex<1, 6>::value == false);
        STATIC_REQUIRE(meta::FindValueByIndex<1, 7>::value == false);
        STATIC_REQUIRE(meta::FindValueByIndex<1, 8>::value == false);
        STATIC_REQUIRE(meta::FindValueByIndex<1, 9>::value == false);


        STATIC_REQUIRE((TestValues[0] == 0) == true);
        STATIC_REQUIRE((TestValues[1] == 1) == true);
        STATIC_REQUIRE((TestValues[2] == 2) == true);
        STATIC_REQUIRE((TestValues[3] == 3) == true);
        STATIC_REQUIRE((TestValues[4] == 4) == true);
        STATIC_REQUIRE((TestValues[5] == 5) == true);
        STATIC_REQUIRE((TestValues[6] == 6) == true);
        STATIC_REQUIRE((TestValues[7] == 7) == true);
        STATIC_REQUIRE((TestValues[8] == 8) == true);
        STATIC_REQUIRE((TestValues[9] == 9) == true);

        STATIC_REQUIRE(meta::TestPredicate<0>::value == false);
        STATIC_REQUIRE(meta::TestPredicate<1>::value == false);
        STATIC_REQUIRE(meta::TestPredicate<2>::value == false);
        STATIC_REQUIRE(meta::TestPredicate<3>::value == false);
        STATIC_REQUIRE(meta::TestPredicate<4>::value == false);
        STATIC_REQUIRE(meta::TestPredicate<5>::value == false);
        STATIC_REQUIRE(meta::TestPredicate<6>::value == false);
        STATIC_REQUIRE(meta::TestPredicate<7>::value == true);
        STATIC_REQUIRE(meta::TestPredicate<8>::value == false);
        STATIC_REQUIRE(meta::TestPredicate<9>::value == false);

        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate, 0, TestValues.size() - 1> == 0);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate, 0, TestValues.size() - 1> == 1);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate, 0, TestValues.size() - 1> == 2);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate, 0, TestValues.size() - 1> == 3);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate, 0, TestValues.size() - 1> == 4);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate, 0, TestValues.size() - 1> == 5);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate, 0, TestValues.size() - 1> == 6);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate, 0, TestValues.size() - 1> == 7);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate, 0, TestValues.size() - 1> == 8);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate, 0, TestValues.size() - 1> == 9);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate, 0, TestValues.size() - 1> == 10);

        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate2, 0, TestValues.size() - 1> == 0);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate2, 0, TestValues.size() - 1> == 1);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate2, 0, TestValues.size() - 1> == 2);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate2, 0, TestValues.size() - 1> == 3);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate2, 0, TestValues.size() - 1> == 4);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate2, 0, TestValues.size() - 1> == 5);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate2, 0, TestValues.size() - 1> == 6);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate2, 0, TestValues.size() - 1> == 7);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate2, 0, TestValues.size() - 1> == 8);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate2, 0, TestValues.size() - 1> == 9);
        STATIC_REQUIRE(meta::BinarySearch_v<TestPredicate2, 0, TestValues.size() - 1> == 10);
    */
}

} // namespace morpheus::meta
