#pragma once

#include <ankerl/unordered_dense.h>

#include <cstdint>
#include <string>
#include <string_view>

namespace morpheus::containers
{

/// \struct string_hash
///     Defines a hasher for string which enable heterogenous overloads as outlined at 
///     <a href="https://github.com/martinus/unordered_dense?tab=readme-ov-file#324-heterogeneous-overloads-using-is_transparent ">unordered_dense</a> 
struct string_hash {
    using is_transparent = void; // enable heterogeneous overloads
    using is_avalanching = void; // mark class as high quality avalanching hash

    [[nodiscard]] auto operator()(std::string_view str) const noexcept -> std::uint64_t {
        return ankerl::unordered_dense::hash<std::string_view>{}(str);
    }
};

namespace details
{

template<typename K, typename V>
struct UnorderdDenseMap {
    using type = ankerl::unordered_dense::map<K, V>;
};

template<typename V>
struct UnorderdDenseMap<std::string, V> {
    using type = ankerl::unordered_dense::map<std::string, V, string_hash, std::equal_to<>>;
};

template<typename V>
struct UnorderdDenseSet {
    using type = ankerl::unordered_dense::set<V>;
};

template<>
struct UnorderdDenseSet<std::string> {
    using type = ankerl::unordered_dense::set<std::string, string_hash, std::equal_to<>>;
};

}

/// \using UnorderdMap
///     Helper alias which ensure users get heterogenous overloads where possible.
template<typename K, typename V>
using UnorderedMap = details::UnorderdDenseMap<K, V>::type;

/// \using UnorderedSet
///     Helper alias which ensure users get heterogenous overloads where possible.
template<typename V>
using UnorderedSet = details::UnorderdDenseSet< V>::type;

}