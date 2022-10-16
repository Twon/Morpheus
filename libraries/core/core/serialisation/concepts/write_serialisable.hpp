#pragma once

#include "core/serialisation/concepts/write_serialiser.hpp"
#include "core/serialisation/concepts/writer_archtype.hpp"
#include "core/serialisation/dispatch.hpp"

#include <concepts>

namespace morpheus::serialisation::concepts
{

template <typename Type>
concept WriteSerialisableFreeStading = requires(WriteSerialiserArchtype& s, Type const& t)
{
    { serialise(s, t) } -> std::same_as<void>;
};

template <typename Type>
concept WriteSerialisableInsrusive = requires(WriteSerialiserArchtype& s, Type const& t)
{
//    NotWriteSerialiser<Serialiser>;
    { t.serialise(s) } -> std::same_as<void>; 
};

template <typename Type>
concept WriteSerialisableNative = requires(WriteSerialiserArchtype& s, Type const& t)
{
//    WriteSerialiser<Serialiser>;
    { s.writer().write(t) } -> std::same_as<void>;
};

template <typename Type>
concept WriteSerialisableStrong = requires(WriteSerialiserArchtype& s, Type const& value)
{
    { serialise(s, value, DispatchSelect<Type>()) } -> std::same_as<void>;
};

template <typename Type>
concept WriteSerialisable = WriteSerialisableFreeStading<Type> or 
                            WriteSerialisableInsrusive<Type> or 
                            WriteSerialisableNative<Type> or
                            WriteSerialisableStrong<Type>;

} // morpheus::serialisation::concepts