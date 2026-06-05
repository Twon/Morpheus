#pragma once

#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"

#include <boost/dynamic_bitset/dynamic_bitset.hpp>

#include <type_traits>

namespace morpheus::serialisation::detail
{

template <concepts::WriteSerialiser Serialiser, typename Block, typename AllocatorOrContainer>
void serialise(Serialiser& serialiser, boost::dynamic_bitset<Block, AllocatorOrContainer> const& bits)
{
    static constexpr std::size_t bits_per_block = boost::dynamic_bitset<Block, AllocatorOrContainer>::bits_per_block;

    if (serialiser.writer().isTextual())
    {
        std::string str;
        boost::to_string(bits, str);
        serialiser.serialise(str);
    }
    else
    {
        serialiser.writer().beginSequence(bits.size());
        for (std::size_t i = 0; i < bits.size(); i += bits_per_block)
        {
            std::uint64_t block = 0;
            auto const maxBit = std::min<std::size_t>(bits_per_block, bits.size() - i);
            for (std::size_t j = 0; j < maxBit; ++j)
            {
                block |= bits[i + j] ? (1uz << j) : 0;
            }
            serialiser.serialise(block);
        }
        serialiser.writer().endSequence();
    }
}

template <concepts::ReadSerialiser Serialiser, typename Block, typename AllocatorOrContainer>
boost::dynamic_bitset<Block, AllocatorOrContainer> deserialise(Serialiser& serialiser, std::type_identity<boost::dynamic_bitset<Block, AllocatorOrContainer>>)
{
    static constexpr std::size_t bits_per_block = boost::dynamic_bitset<Block, AllocatorOrContainer>::bits_per_block;

    if (serialiser.reader().isTextual())
    {
        return boost::dynamic_bitset<Block, AllocatorOrContainer>{serialiser.template deserialise<std::string>()};
    }
    else
    {
        auto const numBits = serialiser.reader().beginSequence();
        boost::dynamic_bitset<Block, AllocatorOrContainer> bits(numBits.value_or(0));
        for (std::size_t i = 0; i < bits.size(); i += bits_per_block)
        {
            Block block = serialiser.template deserialise<Block>();
            auto const maxBit = std::min<std::size_t>(bits_per_block, bits.size() - i);
            for (std::size_t j = 0; j < maxBit; ++j)
            {
                bits[i + j] = (block & (Block(1) << j)) != 0;
            }
        }
        serialiser.reader().endSequence();
        return bits;
    }
}

} // namespace morpheus::serialisation::detail
