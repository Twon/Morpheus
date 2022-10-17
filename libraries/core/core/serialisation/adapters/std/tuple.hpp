#pragma once

#include "core/serialisation/concepts/write_serialiser.hpp"
#include "core/serialisation/concepts/write_serialisable.hpp"

#include <tuple>

namespace morpheus::serialisation::detail
{

template<concepts::WriteSerialiser Serialiser, concepts::WriteSerialisable... T>
void serialise(Serialiser& serialiser, std::tuple<T...> const& value)
{
    serialiser.writer().beginSequence(std::tuple_size<std::tuple<T...>>::value);
    std::apply([&serialiser](auto const&... ts) { (serialiser.serialise(ts), ...); }, value);
    serialiser.writer().endSequence();
}

} // morpheus::serialisation