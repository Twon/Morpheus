#pragma once

#include "morpheus/core/conformance/date.hpp"
#include "morpheus/core/conversion/adapters/std/chrono.hpp"
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

template <concepts::WriteSerialiser Serialiser, typename Rep, typename Period>
void serialise(Serialiser& serialiser, std::chrono::duration<Rep, Period> const& value)
{
    if (serialiser.writer().isTextual())
    {
        serialiser.serialise(conversion::toString(value));
    }
    else
    {
        serialiser.serialise(value.count());
    }
}

template <concepts::ReadSerialiser Serialiser, IsStdChronoDuration T>
T deserialise(Serialiser& serialiser)
{
    if (serialiser.writer().isTextual()) {
        return conversion::fromString(serialiser.template read<std::string>());
    }
    else {
        return T{serialiser.template read<typename T::rep>()};
    }
}

} // namespace morpheus::serialisation::detail