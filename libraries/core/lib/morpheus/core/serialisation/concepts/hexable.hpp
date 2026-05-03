#pragma once

#include <concepts>
#include <cstddef>
#include <type_traits>

namespace morpheus::serialisation::concepts
{

/// \concept Hexable
///     Constraints for a type capable of being text serialised as hexadecimal.
template <typename T>
concept Hexable = std::integral<T> || std::same_as<T, std::byte>;

} // namespace morpheus::serialisation::concepts
