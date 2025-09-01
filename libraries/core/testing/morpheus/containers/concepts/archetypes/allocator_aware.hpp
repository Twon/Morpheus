#pragma once

#include "morpheus/containers/concepts/archetypes/container.hpp"

#include <compare>
#include <memory>

namespace morpheus::containers::concepts::archetypes
{

struct AllocatorAware : public Container
{
    /// The allocator type of the container.
    using allocator_type = std::allocator<int>;

    /// Default constructor
    constexpr AllocatorAware();
    /// Construct the container with a specific allocator.
    constexpr AllocatorAware(allocator_type const&);
    /// Copy constructor
    constexpr AllocatorAware(AllocatorAware const&);
    /// Copy constructor with a specific allocator.
    constexpr AllocatorAware(AllocatorAware const&, allocator_type const&);
    /// Move constructor
    constexpr AllocatorAware(AllocatorAware&&);
    /// Move constructor with a specific allocator.
    constexpr AllocatorAware(AllocatorAware&&, allocator_type const&);

    /// Copy assignment operator
    constexpr AllocatorAware& operator=(AllocatorAware const&);
    /// Move assignment operator
    constexpr AllocatorAware& operator=(AllocatorAware&&);

    /// Spaceship operator
    constexpr auto operator<=>(AllocatorAware const&) const = default;

    /// Get the allocator of the container.
    constexpr allocator_type get_allocator() const noexcept;

    /// Swap the contents of two containers.
    constexpr void swap(AllocatorAware&) noexcept;
};

} // namespace morpheus::containers::concepts::archetypes
