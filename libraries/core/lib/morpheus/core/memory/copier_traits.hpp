#pragma once

#include <type_traits>

namespace morpheus::memory
{

template <class T, class = void>
struct copier_traits_deleter_base
{};

/// \struct copier_traits_deleter_base<T, std::void_t<typename T::deleter_type>>
///     Helper specialisation of copier traits which defaults the deleter type to T::deleter_type when present.
template <class T>
struct copier_traits_deleter_base<T, std::void_t<typename T::deleter_type>>
{
    /// The associated deleter to be used with this copier.
    using deleter_type = typename T::deleter_type;
};

/// Helper specialisation of copier traits which allows defaulting the deleter type with function pointer
/// equivalent matching signature of the function when used with function pointer copier.
template <class U, class V>
struct copier_traits_deleter_base<U* (*)(V)>
{
    /// The associated deleter to be used with this copier.
    using deleter_type = void (*)(U*);
};

// The user may specialize copier_traits<T> per [namespace.std]/2.
template <class T>
struct copier_traits : copier_traits_deleter_base<T, void>
{};

} // namespace morpheus::memory
