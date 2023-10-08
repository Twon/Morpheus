#pragma once

#include "morpheus/core/serialisation/concepts/writer.hpp"

namespace morpheus::serialisation::concepts
{

template <typename Serialiser>
concept WriteSerialiser = requires(Serialiser s) {
    // clang-format off
    { s.writer() } -> Writer;
    // clang-format on
};

template <typename Serialiser>
concept NotWriteSerialiser = not WriteSerialiser<Serialiser>;

} // morpheus::serialisation::concepts
