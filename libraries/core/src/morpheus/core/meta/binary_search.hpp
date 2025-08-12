#pragma once

#include <cstdint>
#include <type_traits>

namespace morpheus::meta
{

template <template <std::size_t> typename Predicate, std::size_t Begin, std::size_t End>
struct BinarySearch;

/// \struct BinarySearch
///     To be used in a SFINAE context to detect if a parameter exists.
/// \tparam Predicate
///     A boolean predicate traits to be tested across the value space limited by Begin and End
/// \tparam Begin The beginning index of the range to search.
/// \tparam End The end index of the range to search.
/// \code
/// \endcode
template <template <std::size_t> typename Predicate, std::size_t Begin, std::size_t End>
struct BinarySearch : std::conditional_t<
    ((End - Begin) <= 1),
    std::integral_constant<std::size_t, Begin>,
    std::conditional_t<
        Predicate<(Begin + End) / 2>::value,
        BinarySearch<Predicate, (Begin + End) / 2, End>,
        BinarySearch<Predicate, Begin, (Begin + End) / 2>
    >
>
{};

template <template <std::size_t> typename Predicate, std::size_t Begin, std::size_t End>
constexpr std::size_t BinarySearch_v = BinarySearch<Predicate, Begin, End>::value;

template <template <std::size_t> typename Predicate, std::size_t Beg, std::size_t End>
struct binary_search;
template <template <std::size_t> typename Predicate, std::size_t Beg, std::size_t End>
using binary_search_base =
    std::conditional_t<(End - Beg <= 1),
    std::integral_constant<std::size_t, Beg>,
    std::conditional_t<Predicate<(Beg + End) / 2>::value,
        binary_search<Predicate, (Beg + End) / 2, End>,
        binary_search<Predicate, Beg, (Beg + End) / 2>>>;
template <template <std::size_t> typename Predicate, std::size_t Beg, std::size_t End>
struct binary_search : binary_search_base<Predicate, Beg, End>
{};
template <template <std::size_t> typename Predicate, std::size_t Beg, std::size_t End>
constexpr std::size_t binary_search_v = binary_search<Predicate, Beg, End>::value;

} // namespace morpheus::meta
