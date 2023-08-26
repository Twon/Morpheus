#pragma once

#include "morpheus/core/serialisation/concepts/reader.hpp"
#include <type_traits>

namespace morpheus::serialisation::concepts
{

template <typename Serialiser>
concept ReadSerialiser = requires(Serialiser s) {
    // clang-format off
    { s.reader() } -> Reader;
    // clang-format on
};

template <typename Serialiser>
concept NotReadSerialiser = not ReadSerialiser<Serialiser>;

} // morpheus::serialisation::concepts