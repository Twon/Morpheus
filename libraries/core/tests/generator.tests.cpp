#include "morpheus/core/concurrency/generator.hpp"
#include "morpheus/core/conformance/coro.hpp"
#include "morpheus/core/conformance/ranges.hpp"

#include <catch2/catch_test_macros.hpp>

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

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
    STATIC_REQUIRE(conf::ranges::range<Generator<int>>);
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

    auto const expectedRange = conf::ranges::views::iota(0, 5) | conf::ranges::views::transform([](auto x) { return x * 5; });
    REQUIRE(conf::ranges::equal(generateSequence(0, 25, 5), expectedRange));
}

namespace
{

/// A minimal allocator that records every allocation and deallocation it performs. Memory is obtained through a
/// rebound std::allocator so the counting allocator can be used to drive a generator's coroutine frame via the
/// std::generator-style std::allocator_arg protocol. The aggregate counts are shared (by pointer) across rebinds so
/// that the std::byte rebound used for the frame and the original instance observe the same tallies.
template <typename T = std::byte>
class CountingAllocator
{
public:
    using value_type = T;

    explicit CountingAllocator(std::vector<std::size_t>& allocations, std::vector<std::size_t>& deallocations) noexcept
        : allocations_(&allocations)
        , deallocations_(&deallocations)
    {}

    template <typename U>
    CountingAllocator(CountingAllocator<U> const& other) noexcept
        : allocations_(other.allocations_)
        , deallocations_(other.deallocations_)
    {}

    [[nodiscard]] T* allocate(std::size_t n)
    {
        allocations_->push_back(n * sizeof(T));
        return std::allocator<T>{}.allocate(n);
    }

    void deallocate(T* p, std::size_t n)
    {
        deallocations_->push_back(n * sizeof(T));
        std::allocator<T>{}.deallocate(p, n);
    }

    template <typename U>
    bool operator==(CountingAllocator<U> const& rhs) const noexcept
    {
        return allocations_ == rhs.allocations_ && deallocations_ == rhs.deallocations_;
    }

    template <typename U>
    bool operator!=(CountingAllocator<U> const& rhs) const noexcept
    {
        return !(*this == rhs);
    }

    std::vector<std::size_t>* allocations_;
    std::vector<std::size_t>* deallocations_;
};

} // namespace

TEST_CASE("Generator allocates the coroutine frame with the supplied allocator", "[morpheus.concurrency.generator.allocator]")
{
    std::vector<std::size_t> allocations;
    std::vector<std::size_t> deallocations;
    CountingAllocator alloc{allocations, deallocations};

    auto generator = [](std::allocator_arg_t, CountingAllocator<>) -> Generator<int, CountingAllocator<>>
    {
        for (int i = 0; i < 5; ++i)
        {
            co_yield i;
        }
    }(std::allocator_arg, alloc);

    REQUIRE(allocations.size() == 1);
    REQUIRE(deallocations.empty());

    auto const expectedRange = conf::ranges::views::iota(0, 5);
    REQUIRE(conf::ranges::equal(generator, expectedRange));

    // Producing all of the values must not allocate or deallocate any further frames.
    REQUIRE(allocations.size() == 1);
    REQUIRE(deallocations.empty());
}

TEST_CASE("Generator deallocates the coroutine frame exactly once with the supplied allocator", "[morpheus.concurrency.generator.allocator]")
{
    std::vector<std::size_t> allocations;
    std::vector<std::size_t> deallocations;
    CountingAllocator alloc{allocations, deallocations};

    {
        auto generator = [](std::allocator_arg_t, CountingAllocator<>) -> Generator<int, CountingAllocator<>>
        {
            for (int i = 0; i < 5; ++i)
            {
                co_yield i;
            }
        }(std::allocator_arg, alloc);

        auto const expectedRange = conf::ranges::views::iota(0, 5);
        REQUIRE(conf::ranges::equal(generator, expectedRange));

        REQUIRE(allocations.size() == 1);
        REQUIRE(deallocations.empty());
    }

    // Destroying the generator must release the single coroutine frame through the same allocator.
    REQUIRE(allocations.size() == 1);
    REQUIRE(deallocations.size() == 1);
    // The deallocation must be exactly the same total size that was allocated.
    REQUIRE(deallocations.front() == allocations.front());
}

TEST_CASE("Allocator is used even for an empty generator that is never iterated", "[morpheus.concurrency.generator.allocator]")
{
    std::vector<std::size_t> allocations;
    std::vector<std::size_t> deallocations;
    CountingAllocator alloc{allocations, deallocations};

    {
        [[maybe_unused]] auto generator = [](std::allocator_arg_t, CountingAllocator<>) -> Generator<int, CountingAllocator<>>
        {
            co_return;
        }(std::allocator_arg, alloc);

        // The coroutine frame is allocated eagerly when the coroutine is created, regardless of iteration.
        REQUIRE(allocations.size() == 1);
        REQUIRE(deallocations.empty());
    }

    REQUIRE(allocations.size() == 1);
    REQUIRE(deallocations.size() == 1);
}

} // namespace morpheus::concurrency
