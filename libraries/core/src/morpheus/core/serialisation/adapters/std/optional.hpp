#pragma once

#include "morpheus/core/meta/is_specialisation.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"

#include <optional>

namespace morpheus::serialisation::detail
{

template <typename T>
concept IsStdOptional = meta::IsSpecialisationOf<std::optional, T>;

template<concepts::WriteSerialiser Serialiser, concepts::WriteSerialisable T>
void serialise(Serialiser& serialiser, std::optional<T> const& value)
{
    serialiser.writer().beginNullable(!value);
    if (value) [[likely]]
        serialiser.serialise(*value);
    serialiser.writer().endNullable();
}

template<concepts::ReadSerialiser Serialiser, IsStdOptional T>
T deserialise(Serialiser& serialiser)
{
    auto const nullable = makeScopedNullable(serialiser.reader());
    if (nullable.value())
        return std::optional<typename T::value_type>();
    else
        return std::optional<typename T::value_type>(serialiser.template deserialise<typename T::value_type>());
}

} // morpheus::serialisation::detail
