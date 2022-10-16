#pragma once

#include "core/serialisation/concepts/read_serialiser.hpp"
#include "core/serialisation/concepts/read_serialisable.hpp"
#include "core/serialisation/concepts/write_serialiser.hpp"
#include "core/serialisation/concepts/write_serialisable.hpp"
#include "core/serialisation/fundamentals.hpp"
#include "core/serialisation/dispatch.hpp"

namespace morpheus::serialisation
{

template<concepts::WriteSerialiser Serialiser, concepts::WriteSerialisableInsrusive Type>
//template<typename Serialiser, typename Type>
void serialise(Serialiser& serialiser, Type const& value, DispatchWeak)
{
    value.serialise(serialiser);
}

template<concepts::WriteSerialiser Serialiser, concepts::WriteSerialisable Type>
//template<typename Serialiser, typename Type>
//template<concepts::WriteSerialiser Serialiser, typename Type>
//template<typename Serialiser, concepts::WriteSerialisable Type>
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


template<typename Serialiser, concepts::ReadSerialisableInsrusive Type>
//template<typename Serialiser, typename Type>
auto deserialise(Serialiser& serialiser, DispatchWeak)
{
    Type value;
    serialiser.reader().beginComposite();
    value.deserialise(serialiser);
    serialiser.reader().endComposite();
    return value;
}

template<typename Serialiser, typename Type>
//    requires concepts::WriteSerialiser<Serialiser, Type> and concepts::WriteSerialisable<Type, Serialiser>
Type deserialiseDispatch(Serialiser& serialiser)
{
    return deserialise<Serialiser, Type>(serialiser, DispatchSelect<Type>());
}

}