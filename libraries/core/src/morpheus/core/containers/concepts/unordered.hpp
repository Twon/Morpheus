#pragma once

#include "morpheus/core/containers/concepts/allocator_aware.hpp"

#include <concepts>
#include <initializer_list>

namespace morpheus::containers::concepts
{

/// \concept Unordered
///     Concept capturing the requirements for an unordered associative container as outline in the standard at
///     <a href="https://eel.is/c++draft/unord.req">[unord.req]</a>, details at
///     <a href="https://en.cppreference.com/w/cpp/named_req/UnorderedAssociativeContainer">UnorderedAssociativeContainerr</a>.
template <typename T>
concept Unordered = AllocatorAware<T> && requires(T t, typename T::value_type v, typename T::size_type s, typename T::iterator i, typename T::key_compare c, typename T::local_iterator n, std::initializer_list<typename T::value_type> il){
    requires (std::default_initializable<typename T::key_compare>) && (std::copy_constructible<typename T::key_compare>);
    { T(c) };
    { T(i, i, c) };
#if (__cpp_lib_containers_ranges >= 202202L)
    { T(std::from_range, ranges::subrange<typename T::iterator>{}, c) };
#endif // (__cpp_lib_containers_ranges >= 202202L)
    { T(il, c) };
    //{ t.emplace() }
};

} // namespace morpheus::containers::concepts
