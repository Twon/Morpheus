#pragma once

#include "core/serialisation/concepts/write_serialiser.hpp"
#include "core/serialisation/concepts/write_serialisable.hpp"

#include <utility>

namespace morpheus::serialisation::detail
{

template<concepts::WriteSerialiser Serialiser, concepts::WriteSerialisable T1, concepts::WriteSerialisable T2>
void serialise(Serialiser& serialiser, std::pair<T1, T2> const& value)
{
    serialiser.writer().beginSequence(std::tuple_size<std::pair<T1, T2>>::value);
    serialiser.serialise(value.first);
    serialiser.serialise(value.second);
    serialiser.writer().endSequence();
}

} // morpheus::serialisation