#pragma once

#include <concepts>
#include <memory>

namespace morpheus::memory::concepts
{

/// \concept Copier
///     A copier object allows for a given input type a return copy of the input object.
template <typename T, typename C>
concept Copier = requires(T t, C c) {
    typename T::deleter_type;
    {
        t(c)
    } -> std::same_as<C*>;
};

/// \struct default_copy
///     Default copier uses default allocation in conjunction with copy assignment operator of T.
// template <class T>
// struct default_copy
// {
//     /// The deleter type to be used to deallocate objects created by the copier.
//     using deleter_type = std::default_delete<T>;

//     /// Create a copy of the input.
//     constexpr T* operator()(T const& t) const { return new T(t); }
// };

} // namespace morpheus::memory::concepts
