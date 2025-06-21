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
    /// The value type of the container.
    using value_type = int;
    /// The reference type of the container.
    using reference = value_type&;
    /// The const reference type of the container.
    using const_reference = value_type const&;
    /// The iterator type of the container.
    using iterator = int*;
    /// The const iterator type of the container.
    using const_iterator = int const *;
    /// The difference type of the container.
    using difference_type = std::ptrdiff_t;
    /// The size type of the container.
    using size_type = std::size_t;

    /// Default constructor
    constexpr Container();
    /// Copy constructor
    constexpr Container(Container const&);
    /// Move constructor
    constexpr Container(Container&&);
    /// Destructor
    constexpr ~Container() = default;
    /// Copy assignment operator
    constexpr Container& operator=(Container const&);
    /// Move assignment operator
    constexpr Container& operator=(Container&&);

    /// Spaceship operator
    constexpr auto operator<=>(Container const&) const = default;

    /// returns an iterator to the beginning
    constexpr iterator begin() noexcept;
    /// returns an iterator to the end
    constexpr iterator end() noexcept;
    /// returns a const iterator to the beginning
    constexpr const_iterator begin() const noexcept;
    /// returns a const iterator to the end
    constexpr const_iterator end() const noexcept;
    /// returns a const iterator to the beginning
    constexpr const_iterator cbegin() const noexcept;
    /// returns a const iterator to the end
    constexpr const_iterator cend() const noexcept;
    /// returns the number of elements
    constexpr size_type size() const noexcept;
    /// returns the maximum number of elements
    constexpr size_type max_size() const noexcept;
    /// returns whether the container is empty
    constexpr bool empty() const noexcept;
};

} // namespace morpheus::containers::concepts::archetypes
