#pragma once

#include "morpheus/core/serialisation/concepts/writer.hpp"

namespace morpheus::serialisation::concepts
{

template <typename Serialiser>
concept WriteSerialiser = requires(Serialiser s)
{
    { s.writer() } -> Writer;
//    { s.template serialise<Type>(t) } -> std::same_as<void>;
};

template <typename Serialiser>
concept NotWriteSerialiser = not WriteSerialiser<Serialiser>;

} // morpheus::serialisation::concepts