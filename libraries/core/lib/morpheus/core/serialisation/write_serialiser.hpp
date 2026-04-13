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

template <concepts::Writer WriterType>
auto WriteSerialiser<WriterType>::serialise(std::size_t size, std::invocable auto f)
{
    mWriter.beginSequence(size);
    f();
    mWriter.endSequence();
}

/*
template<concepts::Writer WriterType>
auto WriteSerialiser<WriterType>::serialise(std::invocable auto f)
{
    mWriter.beginComposite();
    f();
    mWriter.endComposite();
}
*/

template <concepts::Writer WriterType>
auto WriteSerialiser<WriterType>::serialise(bool const null, std::invocable auto f)
{
    mWriter.beginNullable(null);
    f();
    mWriter.endNullable();
}

} // namespace morpheus::serialisation
