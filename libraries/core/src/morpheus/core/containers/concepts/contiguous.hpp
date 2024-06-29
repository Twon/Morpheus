#pragma once

#include "morpheus/core/containers/concepts/sequence.hpp"

#include <concepts>
#include <iterator>

namespace morpheus::containers::concepts
{

/// \concept Contiguous
///     Concept capturing the requirements for a contiguous container, a named requirement outlined in the standard at
///     <a href="https://eel.is/c++draft/container.requirements.general">[container.requirements.general]</a>, details at
///     <a href="https://en.cppreference.com/w/cpp/named_req/ContiguousContainer">ContiguousContainer</a>.
template <typename T>
concept Contiguous = StrictSequence<T> && requires(T t){
    requires std::contiguous_iterator<typename T::iterator>;
    requires std::contiguous_iterator<typename T::const_iterator>;
};

} // namespace morpheus::containers::concepts
