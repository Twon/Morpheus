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

template <typename T>
concept IsStdChronoDuration = meta::IsSpecialisationOf<std::chrono::duration, T>;

template <concepts::WriteSerialiser Serialiser, typename Rep, typename Period>
void serialise(Serialiser& serialiser, std::chrono::duration<Rep, Period> const& value)
{
    if (serialiser.writer().isTextual())
    {
        serialiser.serialise(conversion::toString(value));
    }
    else
    {
// Actually this is a libc++ issue and not exclusivly Clang.
#if (MORPHEUS_COMPILER == MORPHEUS_CLANG_COMPILER)
        // Clang stores std::chrono::duration::rep as a "long long",
        // but std::int64_t is defined as "long" on 64-bit architectures.
        // so if we don't cast it we don't find the appropriat writer handler.
        serialiser.serialise(static_cast<std::int64_t>(value.count()));
#else
        serialiser.serialise(value.count());
#endif // (MORPHEUS_COMPILER == MORPHEUS_CLANG_COMPILER)
    }
}

template <concepts::ReadSerialiser Serialiser, IsStdChronoDuration T>
T deserialise(Serialiser& serialiser)
{
    if (serialiser.reader().isTextual()) {
        return conversion::fromString<T>(serialiser.template deserialise<std::string>()).value();
    }
    else {
        return T{serialiser.template deserialise<typename T::rep>()};
    }
}

} // namespace morpheus::serialisation::detail
