#pragma once

// IWYU pragma: always_keep
#include "morpheus/core/meta/is_specialisation.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"

#include <utility>

namespace morpheus::serialisation::detail
{

template <typename T>
concept IsStdPair = meta::IsSpecialisationOf<std::pair, T>;

template<concepts::WriteSerialiser Serialiser, concepts::WriteSerialisable T1, concepts::WriteSerialisable T2>
void serialise(Serialiser& serialiser, std::pair<T1, T2> const& value)
{
    serialiser.writer().beginSequence(std::tuple_size<std::pair<T1, T2>>::value);
    serialiser.serialise(value.first);
    serialiser.serialise(value.second);
    serialiser.writer().endSequence();
}

template<concepts::ReadSerialiser Serialiser, IsStdPair T>
T deserialise(Serialiser& serialiser)
{
    // More work required to support std::pairs containing references.
    static_assert(!std::is_reference_v<typename T::first_type>);
    static_assert(!std::is_reference_v<typename T::second_type>);

    auto const scope = makeScopedSequence(serialiser.reader(), std::tuple_size<T>::value);
    return T{ serialiser.template deserialise<typename T::first_type>(), serialiser.template deserialise<typename T::second_type>() };
}

} // morpheus::serialisation
