#pragma once

#include "morpheus/core/meta/is_specialisation.hpp"
#include "morpheus/core/conformance/expected.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"

#include <optional>

namespace morpheus::serialisation::detail
{

template <typename T, typename E>
concept IsStdExpected = meta::IsSpecialisationOf<exp_ns::expected, T, E>;

template<concepts::WriteSerialiser Serialiser, concepts::WriteSerialisable T, concepts::WriteSerialisable E>
void serialise(Serialiser& serialiser, std::expected<T, E> const& value)
{
    serialiser.writer().beginComposite();
    serialiser.serialise("state", value);
    if (value) [[likely]]
        serialiser.serialise("value", value.value());
    else
        serialiser.serialise("error", value.error());
    serialiser.writer().endComposite();
}

template<concepts::ReadSerialiser Serialiser, IsStdExpected T>
T deserialise(Serialiser& serialiser)
{
    auto const nullable = makeScopedNullable(serialiser.reader());
    if (nullable.value())
        return exp_ns::expected<typename T::value_type, typename T::error_type>(
            serialiser.template deserialise<typename T::value_type, typename T::error_type>()
        );
    else
        return exp_ns::expected<typename T::value_type, typename T::error_type>(
            serialiser.template deserialise<typename T::value_type, typename T::error_type>()
        );
}

} // morpheus::serialisation::detail