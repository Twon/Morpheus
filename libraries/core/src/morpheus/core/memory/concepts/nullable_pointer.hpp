#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>

namespace morpheus::memory::concepts
{

// clang-format off
// Requires clang-format 18.0 support for AllowShortCompoundRequirementOnASingleLine: true

/// \concept NullablePointer
///     Concept capturing the requirements for an nullable pointer as outline in the standard at
///     <a href="https://eel.is/c++draft/nullablepointer.requirements">[nullablepointer.requirements]</a>.
///
template <typename T>
concept NullablePointer = requires(T t) {
    std::default_initializable<T>;
    std::copy_constructible<T>;
    std::assignable_from<T, T>;
    std::destructible<T>;
    std::equality_comparable<T>;
    std::equality_comparable_with<T, std::nullptr_t>;
    std::swappable<T>;
    { T(nullptr) } -> std::same_as<T>;
    { t = nullptr } -> std::same_as<T&>;
};

// clang-format off

} // namespace morpheus::memory::concepts
