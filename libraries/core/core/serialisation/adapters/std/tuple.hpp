#pragma once

#include "core/serialisation/concepts/write_serialiser.hpp"
#include "core/serialisation/concepts/write_serialisable.hpp"

#include <tuple>

namespace morpheus::serialisation
{

template<typename Serialiser, typename... T>
requires concepts::WriteSerialiser<Serialiser, Type> and concepts::WriteSerialisable<Type, Serialiser>
void serialise(Serialiser& serialiser, std::tuple<T...> const& value)
{
    serialiser.write().beginSequence(std::tuple_size<std::tuple<T...>>::value);
    std::apply([&serialiser](auto const&... ts) { (serialiser.serialize(ts), ...); }, value);
    serialiser.write().endSequence();
}

} // morpheus::serialisation