#pragma once

#include <cstddef>
#include <compare>
#include <iterator>

namespace morpheus::containers::concepts::archetypes
{

// Pull range access functions into scope.
using std::begin;
using std::end;
using std::cbegin;
using std::cend;
using std::size;
using std::empty;

struct Container
{
    using value_type = int;
    using reference = value_type&;
    using const_reference = value_type const&;
    using iterator = int*;
    using const_iterator = int const *;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;

    constexpr Container();
    constexpr Container(Container const&);
    constexpr Container(Container&&);
    constexpr ~Container() = default;
    constexpr Container& operator=(Container const&);
    constexpr Container& operator=(Container&&);

    constexpr auto operator<=>(Container const&) const = default;

    constexpr iterator begin() noexcept;
    constexpr iterator end() noexcept;
    constexpr const_iterator begin() const noexcept;
    constexpr const_iterator end() const noexcept;
    constexpr const_iterator cbegin() const noexcept;
    constexpr const_iterator cend() const noexcept;
    constexpr size_type size() const noexcept;
    constexpr size_type max_size() const noexcept;
    constexpr bool empty() const noexcept;
};

} // namespace morpheus::containers::concepts::archetypes
