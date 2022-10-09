#pragma once

#include "core/serialisation/concepts/read_serialiser.hpp"
#include "core/serialisation/concepts/read_serialisable.hpp"
#include "core/serialisation/concepts/write_serialiser.hpp"
#include "core/serialisation/concepts/write_serialisable.hpp"
#include "core/serialisation/fundamentals.hpp"
#include "core/serialisation/dispatch.hpp"

namespace morpheus::serialisation
{

template<typename Serialiser, typename Type>
requires concepts::WriteSerialisableInsrusive<Serialiser, Type>
void serialise(Serialiser& serialiser, Type const& value, DispatchWeak)
{
    value.serialise(serialiser);
}

template<typename Serialiser, typename Type>
requires concepts::WriteSerialiser<Serialiser, Type> and concepts::WriteSerialisable<Type, Serialiser>
void serialiseDispatch(Serialiser& serialiser, Type const& value)
{
    serialise(serialiser, value, DispatchSelect<Type>());
/*
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
*/
}


template<typename Serialiser, typename Type>
requires concepts::ReadSerialisableInsrusive<Serialiser, Type>
void deserialise(Serialiser& serialiser, DispatchWeak)
{
    return Type{}.deserialise(serialiser);
}

template<typename Serialiser, typename Type>
//    requires concepts::WriteSerialiser<Serialiser, Type> and concepts::WriteSerialisable<Type, Serialiser>
Type deserialiseDispatch(Serialiser& serialiser)
{
    return deserialise<Serialiser, Type>(serialiser, DispatchSelect<Type>());
}

}