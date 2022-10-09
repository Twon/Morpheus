#pragma once

#include "core/serialisation/concepts/write_serialiser.hpp"
#include "core/serialisation/concepts/write_serialisable.hpp"

#include <utility>

namespace morpheus::serialisation
{

template<typename Serialiser, typename T1, typename T2>
requires concepts::WriteSerialiser<Serialiser, Type> and concepts::WriteSerialisable<Type, Serialiser>
void serialise(Serialiser& serialiser, std::pair<T1, T2> const& value)
{
    serialiser.write().beginSequence(std::tuple_size<std::pair<T1, T2>>::value);
    serialiser.serialise(value.first);
    serialiser.serialise(value.second);
    serialiser.write().endSequence();
}

} // morpheus::serialisation