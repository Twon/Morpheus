#pragma once

#include <ankerl/unordered_dense.h>

#include <cstdint>
#include <string>
#include <string_view>

namespace morpheus::containers
{

/// \struct string_hash
///     Defines a hasher for string which enable heterogeneous overloads as outlined at
///     <a href="https://github.com/martinus/unordered_dense?tab=readme-ov-file#324-heterogeneous-overloads-using-is_transparent ">unordered_dense</a>
struct string_hash
{
    using is_transparent = void; ///< Enable heterogeneous overloads
    using is_avalanching = void; ///< Mark class as high quality avalanching hash

    [[nodiscard]] auto operator()(std::string_view str) const noexcept -> std::uint64_t { return ankerl::unordered_dense::hash<std::string_view>{}(str); }
};

namespace details
{

template <typename K, typename V, typename A = std::allocator<std::pair<K, V>>>
struct UnorderdDenseMap
{
    using type = ankerl::unordered_dense::map<K, V, ankerl::unordered_dense::hash<K>, std::equal_to<>, A>;
};

template <typename V, typename A>
struct UnorderdDenseMap<std::string, V, A>
{
    using type = ankerl::unordered_dense::map<std::string, V, string_hash, std::equal_to<>, A>;
};

template <typename V, typename A = std::allocator<V>>
struct UnorderdDenseSet
{
    using type = ankerl::unordered_dense::set<V, ankerl::unordered_dense::hash<V>, std::equal_to<>, A>;
};

template <typename A>
struct UnorderdDenseSet<std::string, A>
{
    using type = ankerl::unordered_dense::set<std::string, string_hash, std::equal_to<>, A>;
};

} // namespace details

/// Helper alias which ensure users get heterogeneous overloads where possible.
template <typename K, typename V, typename A = std::allocator<std::pair<K, V>>>
using UnorderedDenseMap = typename details::UnorderdDenseMap<K, V>::type;

/// Helper alias which ensure users get heterogeneous overloads where possible.
template <typename K, typename A = std::allocator<K>>
using UnorderedDenseSet = typename details::UnorderdDenseSet<K, A>::type;

} // namespace morpheus::containers
