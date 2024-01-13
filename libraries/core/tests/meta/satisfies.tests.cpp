#include "morpheus/core/meta/concepts/satisfies.hpp"

#include <catch2/catch_all.hpp>

#include <type_traits>

namespace morpheus::meta
{

template <typename T, auto C>
concept RangeOver = std::ranges::range<T> and concepts::Satisfies<std::ranges::range_value_t<T>, C>;

template <typename T>
concept HasRangeOfIds = requires(T t)
{
    { t.ids() } -> RangeOver<[]<std::integral>{}>;
};

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
