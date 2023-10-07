#pragma once

#include "morpheus/core/meta/is_string.hpp"
#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"

#include <utility>

namespace morpheus::serialisation
{

namespace detail
{

template <concepts::WriteSerialiser Serialiser, concepts::WriteSerialisableNative T>
void serialise(Serialiser& s, T&& value)
{
    s.writer().write(std::forward<T>(value));
}

template <concepts::ReadSerialiser Serialiser, concepts::ReadSerialisableNative T>
T deserialise(Serialiser& s)
{
    return s.reader().template read<T>();
}

} // namespace detail

} // namespace morpheus::serialisation