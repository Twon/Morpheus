#pragma once

#include "morpheus/containers/concepts/archetypes/container.hpp"

#include <compare>
#include <cstddef>
#include <iterator>

namespace morpheus::containers::concepts::archetypes
{

// Pull range access functions into scope.
using std::crbegin;
using std::crend;
using std::rbegin;
using std::rend;

struct Reversible : Container
{
    /// The reverse iterator type of the container.
    using reverse_iterator = std::reverse_iterator<iterator>;
    /// The const reverse iterator type of the container.
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /// returns an reverse iterator to the beginning
    constexpr reverse_iterator rbegin() noexcept;
    /// returns an reverse iterator to the end
    constexpr reverse_iterator rend() noexcept;
    /// returns a const reverse iterator to the beginning
    constexpr const_reverse_iterator rbegin() const noexcept;
    /// returns a const reverse iterator to the end
    constexpr const_reverse_iterator rend() const noexcept;
};

} // namespace morpheus::containers::concepts::archetypes
