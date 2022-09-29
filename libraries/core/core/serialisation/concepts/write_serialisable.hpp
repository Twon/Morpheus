#pragma once

#include "core/serialisation/concepts/write_serialiser.hpp"

#include <type_traits>

namespace morpheus::serialisation::concepts
{

template <typename Serialiser, typename Type>
concept WriteSerialisableFreeStading = requires(Serialiser s, Type t)
{
    { serialize(s, t) } -> std::same_as<void>;
};

template <typename Serialiser, typename Type>
concept WriteSerialisableInsrusive = requires(Serialiser s, Type t)
{
    NotWriteSerialiser<Serialiser, Type>;
    { t.serialise(s) } -> std::same_as<void>; 
};

template <typename Serialiser, typename Type>
concept WriteSerialisableNative = requires(Serialiser s, Type t)
{
    WriteSerialiser<Serialiser, Type>;
    { s.writer().write(t) } -> std::same_as<void>;
};

template <typename Serialiser, typename Type>
concept WriteSerialisable = WriteSerialisableFreeStading<Serialiser, Type> or 
                            WriteSerialisableInsrusive<Serialiser, Type> or 
                            WriteSerialisableNative<Serialiser, Type>;

} // morpheus::serialisation::concepts