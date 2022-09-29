#pragma once

#include <type_traits>

namespace morpheus::serialisation::concepts
{

template <typename T, typename U>
concept ReadSerialiser = requires(T t)
{
    { t.template deserialize<U>() } -> std::same_as<U>;
}

} // morpheus::serialisation::concepts