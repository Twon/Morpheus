#pragma once

#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"

#include <bitset>
#include <type_traits>

namespace morpheus::serialisation::detail
{

template <concepts::WriteSerialiser Serialiser, std::size_t N>
void serialise(Serialiser& serialiser, std::bitset<N> const& bits)
{
    static constexpr std::size_t bits_per_byte = 8;
    static constexpr std::size_t bits_per_uint64 = sizeof(std::uint64_t) * bits_per_byte;

    if (serialiser.writer().isTextual())
    {
        serialiser.serialise(bits.to_string());
    }
    else if (bits.size() <= bits_per_uint64)
    {
        serialiser.serialise(static_cast<std::uint64_t>(bits.to_ullong()));
    }
    else
    {
        serialiser.writer().beginSequence(bits.size());
        for (std::size_t i = 0; i < bits.size(); i += bits_per_uint64)
        {
            std::uint64_t block = 0;
            auto const maxBit = std::min<std::size_t>(64uz, bits.size() - i);
            for (std::size_t j = 0uz; j < maxBit; ++j)
            {
                block |= bits[i + j] ? (1uz << j) : 0;
            }
            serialiser.serialise(block);
        }
        serialiser.writer().endSequence();
    }
}

template <concepts::ReadSerialiser Serialiser, std::size_t N>
std::bitset<N> deserialise(Serialiser& serialiser, std::type_identity<std::bitset<N>>)
{
    static constexpr std::size_t bits_per_byte = 8;
    static constexpr std::size_t bits_per_uint64 = sizeof(std::uint64_t) * bits_per_byte;

    if (serialiser.reader().isTextual())
    {
        return std::bitset<N>{serialiser.template deserialise<std::string>()};
    }
    else if (N <= bits_per_uint64)
    {
        return std::bitset<N>{serialiser.template deserialise<std::uint64_t>()};
    }
    else
    {
        std::bitset<N> bits;
        [[maybe_unused]] auto const numBlocks = serialiser.reader().beginSequence();
        for (std::size_t i = 0; i < bits.size(); i += bits_per_uint64)
        {
            std::uint64_t block = serialiser.template deserialise<std::uint64_t>();
            auto const maxBit = std::min<std::size_t>(64uz, bits.size() - i);
            for (std::size_t j = 0uz; j < maxBit; ++j)
            {
                bits[i + j] = (block & (1uz << j)) != 0;
            }
        }
        serialiser.reader().endSequence();
        return bits;
    }
}

} // namespace morpheus::serialisation::detail
