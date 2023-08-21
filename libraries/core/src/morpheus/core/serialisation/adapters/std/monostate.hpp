#pragma once

#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"

#include <variant>

namespace morpheus::serialisation::detail
{

template <concepts::WriteSerialiser Serialiser>
void serialise(Serialiser& serialiser, std::monostate)
{
    serialiser.writer().beginComposite();
    serialiser.writer().endComposite();
}

template <concepts::ReadSerialiser Serialiser, std::same_as<std::monostate> T>
T deserialise(Serialiser& serialiser)
{
    serialiser.reader().beginComposite();
    serialiser.reader().endComposite();
    return T{};
}

} // namespace morpheus::serialisation::detail