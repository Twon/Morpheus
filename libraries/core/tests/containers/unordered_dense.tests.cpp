#include "morpheus/core/containers/unordered_dense.hpp"

#include <catch2/catch_all.hpp>

#include <string>

namespace morpheus::containers::concepts
{

TEMPLATE_TEST_CASE("Verify unordered dense map aliases work correctly", "[morpheus.containers.unordered.dense.map]", std::string, int)
{
    auto const values = std::vector{1, 2, 3, 4, 5};
    UnorderedMap<TestType, int> container;

    for (auto const& value : values)
    {
        auto const asTestType = [](auto const v)
        {
            if constexpr (std::is_same_v<TestType, std::string>)
            {
                return std::to_string(v);
            }
            else
            {
                return v;
            }
        };

        auto const key = asTestType(value);
        container[key] = value;
        REQUIRE(container[key] == value);
    }
}

TEMPLATE_TEST_CASE("Verify unordered dense set aliases work correctly", "[morpheus.containers.unordered.dense.set]", std::string, int)
{
    auto const values = std::vector{1, 2, 3, 4, 5};
    UnorderedSet<TestType> container;

    for (auto const& value : values)
    {
        auto const asTestType = [](auto const v)
        {
            if constexpr (std::is_same_v<TestType, std::string>)
            {
                return std::to_string(v);
            }
            else
            {
                return v;
            }
        };

        auto const key = asTestType(value);
        container.insert(key);
        REQUIRE(container.contains(key));
    }
}

} // namespace morpheus::containers::concepts
