#pragma once

#include "core/serialisation/concepts/reader.hpp"
#include <type_traits>

namespace morpheus::serialisation::concepts
{

template <typename T, typename U>
concept ReadSerialiser = requires(T t)
{
    { t.reader() } -> Reader;
    { t.template deserialise<U>() } -> std::same_as<U>;
};

template <typename Serialiser, typename Type>
concept NotReadSerialiser = not ReadSerialiser<Serialiser, Type>;

} // morpheus::serialisation::concepts