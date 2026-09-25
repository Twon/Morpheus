#pragma once

// IWYU pragma: always_keep
#include "morpheus/core/serialisation/adapters/std/ranges.hpp"

#include <array>

namespace morpheus::serialisation::detail
{

template <concepts::WriteSerialiser Serialiser, typename T, std::size_t N>
void serialise(Serialiser& s, std::array<T, N> const& value)
{
    s.writer().beginSequence(N);
    for (auto const& elem : value)
    {
        s.serialise(elem);
    }
    s.writer().endSequence();
}

template <concepts::ReadSerialiser Serialiser, typename T, std::size_t N>
std::array<T, N> deserialise(Serialiser& s, std::type_identity<std::array<T, N>>)
{
    s.reader().beginSequence();
    std::array<T, N> result{};

    for (auto& elem : result)
    {
        elem = s.template deserialise<T>();
    }
    s.reader().endSequence();

    return result;
}

} // namespace morpheus::serialisation::detail
