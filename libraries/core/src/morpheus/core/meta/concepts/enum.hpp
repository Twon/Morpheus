#pragma once

#include <type_traits>

namespace morpheus::meta::concepts
{

template <typename T>
concept Enum = std::is_enum_v<T>;

} // namespace morpheus::meta::concepts
