#pragma once

// IWYU pragma: always_keep
#include "morpheus/core/base/exceptions.hpp"
#include "morpheus/core/conformance/value_types.hpp"
#include "morpheus/core/meta/is_specialisation.hpp"
#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"

#include <type_traits>

namespace morpheus::serialisation::detail
{

template <typename T>
concept IsStdIndirect = meta::IsSpecialisationOf<conf::vt::indirect, T>;

template <concepts::WriteSerialiser Serialiser, concepts::WriteSerialisable T, typename A>
void serialise(Serialiser& serialiser, conf::vt::indirect<T, A> const& value)
{
    if (value.valueless_after_move()) [[unlikely]]
        throwRuntimeException("Indirect value is valueless after move.");

    serialiser.writer().beginComposite();
    serialiser.serialise("value", *value);
    serialiser.writer().endComposite();
}

template <concepts::ReadSerialiser Serialiser, IsStdIndirect T>
T deserialise(Serialiser& serialiser, std::type_identity<T>)
{
    auto const composite = makeScopedComposite(serialiser.reader());
    return conf::vt::indirect<typename T::value_type, typename T::allocator_type>(serialiser.template deserialise<typename T::value_type>("value"));
}

} // namespace morpheus::serialisation::detail
