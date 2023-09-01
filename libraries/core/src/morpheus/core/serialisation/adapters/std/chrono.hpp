#pragma once

#include "morpheus/core/meta/is_specialisation.hpp"
#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"

#include <chrono>

namespace morpheus::serialisation::detail
{

template <typename Rep, typename Period>
concept IsStdChronoDuration = meta::IsSpecialisationOf<std::chrono::duration, Rep, Period>;

template <concepts::WriteSerialiser Serialiser, concepts::WriteSerialisable Rep, concepts::WriteSerialisable Period>
void serialise(Serialiser& serialiser, std::chrono::duration<Rep, Period> const& value)
{
    if (serialiser.isTextual())
    {

    }
    else
    {

    }
}

template <concepts::ReadSerialiser Serialiser, IsStdChronoDuration T>
T deserialise(Serialiser& serialiser)
{
    if (serialiser.isTextual()) {
    }
    else {
    }

    auto const nullable = makeScopedNullable(serialiser.reader());
    if (nullable.value())
        return std::optional<typename T::value_type>();
    else
        return std::optional<typename T::value_type>(serialiser.template deserialise<typename T::value_type>());
}

} // namespace morpheus::serialisation::detail