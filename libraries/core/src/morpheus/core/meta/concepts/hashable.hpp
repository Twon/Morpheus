#pragma once

#include <functional>

namespace morpheus::meta::concepts
{

template <class T>
concept IsHashable = requires(T t) { std::hash<T>{}(t); };

} // namespace morpheus::meta::concepts