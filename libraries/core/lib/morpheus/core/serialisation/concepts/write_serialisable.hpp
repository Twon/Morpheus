#pragma once

#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/writer_archetype.hpp"

#include <concepts>

namespace morpheus::serialisation::concepts
{

template <typename Type>
concept WriteSerialisableFreeStading = requires(WriteSerialiserArchtype& s, Type const& t) {
    { serialise(s, t) } -> std::same_as<void>;
};

template <typename Type>
concept WriteSerialisableInsrusive = requires(WriteSerialiserArchtype& s, Type const& t) {
    { t.serialise(s) } -> std::same_as<void>;
};

template <typename Type>
concept WriteSerialisableNative = requires(WriteSerialiserArchtype& s, Type const t) {
    { s.writer().write(t) } -> std::same_as<void>;
};

template <typename Type>
concept WriteSerialisable = WriteSerialisableFreeStading<Type> or WriteSerialisableInsrusive<Type> or WriteSerialisableNative<Type>;

} // namespace morpheus::serialisation::concepts
