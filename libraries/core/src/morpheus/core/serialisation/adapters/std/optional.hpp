#pragma once

#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"

#include <optional>

namespace morpheus::serialisation::detail
{

template<concepts::WriteSerialiser Serialiser, concepts::WriteSerialisable T>
void serialise(Serialiser& serialiser, std::optional<T> const& value)
{
    serialiser.writer().beginNullable(!value);
    if (value) [[likely]]
        serialiser.serialise(*value);
    serialiser.writer().endNullable();
}

} // morpheus::serialisation::detail