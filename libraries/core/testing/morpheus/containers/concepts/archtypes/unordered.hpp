#pragma once

#include "morpheus/containers/concepts/archtypes/allocator_aware.hpp"

#include <compare>
#include <functional>

namespace morpheus::containers::concepts::archtypes
{

struct Unordered : public AllocatorAware
{
    using key_compare = std::less<int>;
    using value_compare = key_compare;
    using node_type = int;

    using AllocatorAware::AllocatorAware;

    constexpr Unordered();
    constexpr Unordered(key_compare const&);
    constexpr Unordered(iterator, iterator, key_compare const&);
#if (__cpp_lib_containers_ranges >= 202202L)
    constexpr Unordered(std::from_range_t, ranges::range auto, key_compare const&);
#endif // (__cpp_lib_containers_ranges >= 202202L)
    constexpr Unordered(std::initializer_list<int>, key_compare const&);
    constexpr Unordered(Unordered const&);
    constexpr Unordered(Unordered&&);
    constexpr Unordered& operator=(Unordered const&);
    constexpr Unordered& operator=(Unordered&&);
    constexpr Unordered& operator=(std::initializer_list<int>);

    constexpr key_compare key_comp() const;
    constexpr value_compare value_comp() const;
    
    //constexpr std::pair<iterator, bool> emplace(auto... args);
    //constexpr std::pair<iterator, bool> emplace(auto... args);

    constexpr auto operator<=>(Unordered const&) const = default;


};

} // namespace morpheus::containers::concepts::archtypes 
