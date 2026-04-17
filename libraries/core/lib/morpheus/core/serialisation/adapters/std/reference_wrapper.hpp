#pragma once

#include "morpheus/core/meta/is_specialisation.hpp"
#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"

#include <functional>

namespace morpheus::serialisation::detail
{

template <typename T>
concept IsStdRefWrapper = meta::IsSpecialisationOf<std::reference_wrapper, T>;

template <concepts::WriteSerialiser Serialiser, concepts::WriteSerialisable T>
void serialise(Serialiser& serialiser, std::reference_wrapper<T> const& value)
{
    serialiser.serialise(value.get());
}

template <concepts::ReadSerialiser Serialiser, IsStdRefWrapper T>
void deserialise(Serialiser& serialiser, std::reference_wrapper<typename T::type> ref)
{
    ref.get() = serialiser.template deserialise<typename T::type>();
}

} // namespace morpheus::serialisation::detail
