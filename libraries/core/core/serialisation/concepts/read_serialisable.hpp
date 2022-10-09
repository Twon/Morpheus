#pragma once

#include <type_traits>

namespace morpheus::serialisation::concepts
{

template <typename Serialiser, typename Type>
concept ReadSerialisableFreeStading = requires(Serialiser s, Type t)
{
    { deserialise(s, t) } -> std::same_as<Type>;
};

template <typename Serialiser, typename Type>
concept ReadSerialisableInsrusive = requires(Serialiser s, Type t)
{
    NotReadSerialiser<Serialiser, Type>;
    { t.deserialise(s) } -> std::same_as<Type>;
};

template <typename Serialiser, typename Type>
concept ReadSerialisableNative = requires(Serialiser s, Type t)
{
    ReadSerialiser<Serialiser, Type>;
    { s.reader().template read<Type>() } -> std::same_as<Type>;
};

template <typename Serialiser, typename Type>
concept ReadSerialisable = ReadSerialisableFreeStading<Serialiser, Type> or
                           ReadSerialisableInsrusive<Serialiser, Type> or 
                           ReadSerialisableNative<Serialiser, Type>;

} // morpheus::serialisation::concepts