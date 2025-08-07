#pragma once

// IWYU pragma: always_keep
#include "morpheus/core/meta/is_specialisation.hpp"
#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"
#include <memory>

namespace morpheus::serialisation::detail
{

template <typename T>
concept IsStdUniquePtr = meta::IsSpecialisationOf<std::unique_ptr, T>;

template <concepts::WriteSerialiser Serialiser, concepts::WriteSerialisable T>
void serialise(Serialiser& serialiser, std::unique_ptr<T> const& value)
{
    serialiser.writer().beginNullable(!value);
    if (value) [[likely]]
        serialiser.serialise(*value);
    serialiser.writer().endNullable();
}

template <concepts::ReadSerialiser Serialiser, IsStdUniquePtr T>
T deserialise(Serialiser& serialiser)
{
    auto const nullable = makeScopedNullable(serialiser.reader());
    if (nullable.value())
        return std::unique_ptr<typename T::element_type>();
    else
        return std::make_unique<typename T::element_type>(serialiser.template deserialise<typename T::element_type>());
}

} // namespace morpheus::serialisation::detail
