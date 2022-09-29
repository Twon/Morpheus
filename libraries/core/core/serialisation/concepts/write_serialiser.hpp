#pragma once

#include "core/serialisation/concepts/writer.hpp"
#include <type_traits>

namespace morpheus::serialisation::concepts
{

template <typename Serialiser, typename Type>
concept WriteSerialiser = requires(Serialiser s, Type t)
{
    { s.writer() } -> Writer;
    { s.template serialise<Type>(t) } -> std::same_as<void>;
};

template <typename Serialiser, typename Type>
concept NotWriteSerialiser = not WriteSerialiser<Serialiser, Type>;

} // morpheus::serialisation::concepts