#pragma once

#include "morpheus/core/serialisation/concepts/reader_archetype.hpp"

#include <concepts>
#include <type_traits>

namespace morpheus::serialisation::concepts
{

template <typename Type>
concept ReadSerialisableFactory = requires(ReadSerialiserArchetype s) {
    { deserialise<Type>(s) } -> std::same_as<Type>;
};

template <typename Type>
concept ReadSerialisableSink = requires(ReadSerialiserArchetype s, Type t) {
    { deserialise_to(s, t) } -> std::same_as<void>;
};

template <typename Type>
concept ReadSerialisableInsrusive = requires(ReadSerialiserArchetype s, Type t) {
    { t.deserialise(s) } -> std::same_as<void>;
};

template <typename Type>
concept ReadSerialisableNative = requires(ReadSerialiserArchetype s, Type t) {
    { s.reader().template read<Type>() } -> std::same_as<Type>;
};

template <typename Type>
concept ReadSerialisable = ReadSerialisableFactory<Type> || ReadSerialisableSink<Type> || ReadSerialisableInsrusive<Type> || ReadSerialisableNative<Type>;

} // namespace morpheus::serialisation::concepts
