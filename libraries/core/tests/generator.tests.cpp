#include "morpheus/core/concurrency/generator.hpp"
#include "morpheus/core/conformance/coro.hpp"
#include "morpheus/core/conformance/ranges.hpp"

#include <catch2/catch_test_macros.hpp>

#include <concepts>
#include <cstddef>
#include <type_traits>

namespace morpheus::concurrency
{

TEST_CASE("Test a iterator traits hold true for generator iterators", "[morpheus.concurrency.generator.iterator_traits]")
{
    STATIC_REQUIRE(std::is_same_v<std::iterator_traits<Generator<int>::iterator>::difference_type, std::ptrdiff_t>);
    STATIC_REQUIRE(std::is_same_v<std::iterator_traits<Generator<int>::iterator>::value_type, int>);
    STATIC_REQUIRE(std::is_same_v<std::iterator_traits<Generator<int>::iterator>::pointer, int const*>);
    STATIC_REQUIRE(std::is_same_v<std::iterator_traits<Generator<int>::iterator>::reference, int const&>);
    STATIC_REQUIRE(std::is_same_v<std::iterator_traits<Generator<int>::iterator>::iterator_category, std::input_iterator_tag>);
}

TEST_CASE("Ensure generator iterators meet required concepts", "[morpheus.concurrency.generator.concepts]")
{
    STATIC_REQUIRE(std::indirectly_readable<Generator<int>::iterator>);

    STATIC_REQUIRE(std::weakly_incrementable<Generator<int>::iterator>);
    STATIC_REQUIRE(std::semiregular<Generator<int>::iterator>);
    STATIC_REQUIRE(ranges::range<Generator<int>>);
}

TEST_CASE("Test a simple integrer based coroutine", "[morpheus.concurrency.generator]")
{
    auto generateSequence = [](int start = 0, int stop = 5, int step = 1) noexcept -> Generator<int>
    {
        for (int i = start; i < stop; i += step)
        {
            co_yield i;
        }
    };

    auto const expectedRange = ranges::views::iota(0, 5) | ranges::views::transform([](auto x) { return x * 5; });
    REQUIRE(ranges::equal(generateSequence(0, 25, 5), expectedRange));
}

} // namespace morpheus::concurrency
