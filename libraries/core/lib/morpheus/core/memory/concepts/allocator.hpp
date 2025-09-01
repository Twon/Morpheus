#pragma once

#include "morpheus/core/memory/concepts/nullable_pointer.hpp"

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <memory>

namespace morpheus::memory::concepts
{

// clang-format off
// Requires clang-format 18.0 support for AllowShortCompoundRequirementOnASingleLine: true

/// \concept Allocator
///     Concept capturing the requirements for an allocator as outline in the standard at
///     <a href="https://eel.is/c++draft/allocator.requirements">[allocator.requirements]</a>.
/// \par
///     Allocators provide a number of services:
///      - Perform allocation, construction, destruction and deallocation.
///      - Separate allocation from construction,
///      - Separate deallocation from destruction.
///      - Encapsulate information about the allocation strategy.
///      - Encapsulate information about the addressing model.
///      - Hide memory management and addressing model details from users.
///      - Support the reuse of an allocation strategy across allocation users.
/// \note
///     https://rawgit.com/google/cxx-std-draft/allocator-paper/allocator_user_guide.html#reqs
template <template <typename> class A, typename T>
concept Allocator = requires(A<T> a, typename std::allocator_traits<A<T>>::size_type s, typename std::allocator_traits<A<T>>::pointer p) {
    requires std::same_as<typename A<T>::value_type, T>;
    requires NullablePointer<typename std::allocator_traits<A<T>>::pointer>;
    requires NullablePointer<typename std::allocator_traits<A<T>>::const_pointer>;
    requires std::unsigned_integral<typename std::allocator_traits<A<T>>::size_type>;
    requires std::signed_integral<typename std::allocator_traits<A<T>>::difference_type>;

    { a.allocate(s) } -> std::same_as<typename std::allocator_traits<A<T>>::pointer>;
    { a.deallocate(p, s) } -> std::same_as<void>;

#if (__cpp_lib_allocate_at_least >= 202302L )
    { a.allocate_at_least(s) } -> std::same_as<std::allocation_result<typename std::allocator_traits<A<T>>::pointer, typename std::allocator_traits<A<T>>::size_type>>;
#endif
};

// clang-format on

} // namespace morpheus::memory::concepts
