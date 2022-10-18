#pragma once

#include "core/meta/is_string.hpp"
#include "core/serialisation/concepts/read_serialisable.hpp"
#include "core/serialisation/concepts/write_serialisable.hpp"

namespace morpheus::serialisation
{

namespace detail {

template<concepts::WriteSerialiser Serialiser, concepts::WriteSerialisableNative T>
void serialise(Serialiser& s, T const& value)
{
    s.writer().write(value);
}

template<concepts::ReadSerialiser Serialiser, concepts::ReadSerialisableNative T>
T deserialise(Serialiser& s)
{
    return s.reader().template read<T>();
}

}
//template<class SerializerType, typename T> requires std::is_string_v<T> or is_string_view_v<T>
//void serialise(SerializerType& s, T const& value, DispatchStrong)
//{
//    s.writer().write(value);
//}


}