#pragma once

#include "morpheus/core/serialisation/concepts/reader.hpp"
#include <type_traits>

namespace morpheus::serialisation::concepts
{

template <typename Serialiser>
concept ReadSerialiser = requires(Serialiser s)
{
//    true == true
    { s.reader() } -> Reader;
//    { s.template deserialise<Type>() } -> std::same_as<Type>;
};

template <typename Serialiser>
concept NotReadSerialiser = not ReadSerialiser<Serialiser>;

} // morpheus::serialisation::concepts