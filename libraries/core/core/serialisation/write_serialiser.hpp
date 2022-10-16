#pragma once

#include "core/serialisation/write_serialiser_decl.hpp"
#include "core/serialisation/serialise.hpp"

namespace morpheus::serialisation
{

template<concepts::Writer WriterType>
template<typename T>
void WriteSerialiser<WriterType>::serialise(T const& value)
{
    serialiseDispatch(*this, value);
}

template<concepts::Writer WriterType>
template<typename T>
void WriteSerialiser<WriterType>::serialise(std::string_view const key, T const& value)
{
    mWriter.beginValue(key);
    serialiseDispatch(*this, value);
    mWriter.endValue();
}

}