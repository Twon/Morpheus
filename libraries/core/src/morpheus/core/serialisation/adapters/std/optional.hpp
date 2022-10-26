#pragma once

#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"

#include <optional>

namespace morpheus::serialisation::detail
{

template<concepts::WriteSerialiser Serialiser, concepts::WriteSerialisable T>
void serialise(Serialiser& serialiser, std::optional<T> const& value)
{
//    serialiser.write().beginComposite();
//    serialiser.serialise(value.first);
//    serialiser.serialise(value.second);
//    serialiser.write().beginComposite();
}

} // morpheus::serialisation