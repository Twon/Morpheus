#pragma once

#include "morpheus/core/serialisation/serialise.hpp"
#include "morpheus/core/serialisation/write_serialiser_decl.hpp"

namespace morpheus::serialisation
{

template <concepts::Writer WriterType>
template <typename T>
void WriteSerialiser<WriterType>::serialise(T const& value)
{
    serialisation::serialise(*this, value);
}

template <concepts::Writer WriterType>
template <typename T>
void WriteSerialiser<WriterType>::serialise(std::string_view const key, T const& value)
{
    mWriter.beginValue(key);
    serialisation::serialise(*this, value);
    mWriter.endValue();
}

} // namespace morpheus::serialisation
