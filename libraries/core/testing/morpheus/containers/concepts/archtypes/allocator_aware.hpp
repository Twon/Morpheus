#pragma once

#include "morpheus/containers/concepts/archtypes/container.hpp"

#include <compare>
#include <memory>

namespace morpheus::containers::concepts::archtypes
{

struct AllocatorAware : public Container
{
    using allocator_type = std::allocator<int>;

    constexpr AllocatorAware();
    constexpr AllocatorAware(allocator_type const&);
    constexpr AllocatorAware(AllocatorAware const&);
    constexpr AllocatorAware(AllocatorAware const&, allocator_type const&);
    constexpr AllocatorAware(AllocatorAware&&);
    constexpr AllocatorAware(AllocatorAware&&, allocator_type const&);

    constexpr AllocatorAware& operator=(AllocatorAware const&);
    constexpr AllocatorAware& operator=(AllocatorAware&&);

    constexpr auto operator<=>(AllocatorAware const&) const = default;

    constexpr allocator_type get_allocator() const noexcept;

    constexpr void swap(AllocatorAware&) noexcept;
};

} // namespace morpheus::containers::concepts::archtypes
