#pragma once

// IWYU pragma: always_keep
#include "morpheus/core/conformance/expected.hpp"
#include "morpheus/core/meta/is_specialisation.hpp"
#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"

namespace morpheus::serialisation::detail
{

template <typename T>
concept IsStdExpected = meta::IsSpecialisationOf<conf::exp::expected, T>;

template <concepts::WriteSerialiser Serialiser, concepts::WriteSerialisable T, concepts::WriteSerialisable E>
void serialise(Serialiser& serialiser, conf::exp::expected<T, E> const& value)
{
    serialiser.writer().beginComposite();
    serialiser.serialise("state", value.has_value());
    if (value.has_value()) [[likely]]
        serialiser.serialise("value", value.value());
    else
        serialiser.serialise("error", value.error());
    serialiser.writer().endComposite();
}

template <concepts::ReadSerialiser Serialiser, IsStdExpected T>
T deserialise(Serialiser& serialiser)
{
    auto const composite = makeScopedComposite(serialiser.reader());
    auto const has_value = serialiser.template deserialise<bool>("state");
    if (has_value)
        return conf::exp::expected<typename T::value_type, typename T::error_type>(serialiser.template deserialise<typename T::value_type>("value"));
    else
        return conf::exp::expected<typename T::value_type, typename T::error_type>(
            conf::exp::unexpected(serialiser.template deserialise<typename T::error_type>("error")));
}

} // namespace morpheus::serialisation::detail
