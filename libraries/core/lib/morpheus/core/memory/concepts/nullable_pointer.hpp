#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>

namespace morpheus::memory::concepts
{

/// \concept NullablePointer
///     Concept capturing the requirements for a nullable pointer, a named requirement outlined in the standard at
///     <a href="https://eel.is/c++draft/nullablepointer.requirements">[nullablepointer.requirements]</a>, details at
///     <a href="https://en.cppreference.com/w/cpp/named_req/NullablePointer">NullablePointer</a>.
template <typename T>
concept NullablePointer = requires(T t) {
    requires std::default_initializable<T>;
    requires std::copy_constructible<T>;
    requires std::assignable_from<T&, T>;
    requires std::destructible<T>;
    requires std::equality_comparable<T>;
    requires std::equality_comparable_with<T, std::nullptr_t>;
    requires std::swappable<T>;
    { T(nullptr) } -> std::same_as<T>;
    { t = nullptr } -> std::same_as<T&>;
};

} // namespace morpheus::memory::concepts
