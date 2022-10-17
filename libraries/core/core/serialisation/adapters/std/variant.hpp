#pragma once

#include "core/serialisation/concepts/write_serialiser.hpp"
#include "core/serialisation/concepts/write_serialisable.hpp"

#include <variant>

namespace morpheus::serialisation::detail
{

template<concepts::WriteSerialiser Serialiser, concepts::WriteSerialisable... T>
void serialise(Serialiser& serialiser, std::variant<T...> const& value)
{
//    serialiser.write().beginComposite();
//    serialiser.serialise(value.first);
//    serialiser.serialise(value.second);
//    serialiser.write().beginComposite();
}

} // morpheus::serialisation