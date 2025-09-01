#pragma once

#include <type_traits>

namespace morpheus::meta::concepts
{

/// \concept Enum
///     Verifies a given T as an enumerated type.
template <typename T>
concept Enum = std::is_enum_v<T>;

} // namespace morpheus::meta::concepts
