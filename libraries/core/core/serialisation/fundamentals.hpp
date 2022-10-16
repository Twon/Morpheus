#pragma once

#include "core/meta/is_string.hpp"
#include "core/serialisation/concepts/read_serialisable.hpp"
#include "core/serialisation/concepts/write_serialisable.hpp"
#include "core/serialisation/dispatch.hpp"

namespace morpheus::serialisation
{

template<class SerializerType, concepts::WriteSerialisableNative T>
void serialise(SerializerType& s, T const& value, DispatchStrong)
{
    s.writer().write(value);
}

template<class SerializerType, concepts::ReadSerialisableNative T>
T deserialise(SerializerType& s, DispatchStrong)
{
    return s.reader().template read<T>();
}


//template<class SerializerType, typename T> requires std::is_string_v<T> or is_string_view_v<T>
//void serialise(SerializerType& s, T const& value, DispatchStrong)
//{
//    s.writer().write(value);
//}


}