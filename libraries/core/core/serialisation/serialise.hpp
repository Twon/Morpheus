#pragma once

#include "core/serialisation/concepts/write_serialiser.hpp"
#include "core/serialisation/concepts/write_serialisable.hpp"

namespace morpheus::serialisation
{

template<typename Serialiser, typename Type>
requires concepts::WriteSerialiser<Serialiser, Type> and concepts::WriteSerialisable<Type, Serialiser>
void serialiseDispatch(Serialiser& serialiser, Type const& value)
{
    if constexpr (concepts::WriteSerialisableFreeStading<Serialiser, Type>)
    {
        serialise(serialiser, value);
    }
    else if constexpr (concepts::WriteSerialisableInsrusive<Serialiser, Type>)
    {
        value.serialise(serialiser);
    }
    else if constexpr (concepts::WriteSerialisableNative<Serialiser, Type>)
    {
        serialiser.writer().write(value);
    }
}

}