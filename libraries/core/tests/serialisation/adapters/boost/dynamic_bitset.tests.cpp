#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/core/serialisation/adapters/boost/dynamic_bitset.hpp"
#include "morpheus/core/serialisation/mock/reader.hpp"
#include "morpheus/core/serialisation/mock/serialisers.hpp"
#include "morpheus/core/serialisation/mock/writer.hpp"
#include "morpheus/core/serialisation/read_serialiser.hpp"
#include "morpheus/core/serialisation/write_serialiser.hpp"

#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <catch2/catch_test_macros.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace morpheus::serialisation
{

using namespace ::testing;
using namespace std::literals::string_view_literals;

using BitsetType = boost::dynamic_bitset<std::uint64_t>;

std::string toString(BitsetType const& bits)
{
    std::string result;
    boost::to_string(bits, result);
    return result;
}

std::string toBitString(conf::ranges::range auto const& values)
{
    BitsetType bits(values.begin(), values.end());
    return toString(bits);
}

TEST_CASE("Verify serialisation of boost::dynamic_bitset", "[morpheus.serialisation.boost.dynamic_bitset.serialise]")
{
    GIVEN("A boost::dynamic_bitset holding a 64-bit value")
    {
        constexpr std::uint64_t actualValue = 0xFEDCBA9876543210;
        auto const asRange = std::vector{actualValue};
        auto const expectedStringValue = toBitString(asRange);
        auto const value = BitsetType(asRange.begin(), asRange.end());

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), isTextual()).WillOnce(Return(true));
            EXPECT_CALL(serialiser.writer(), write(Matcher<std::string_view>(Eq(expectedStringValue)))).Times(1);

            WHEN("Serialising the boost::dynamic_bitset")
            {
                serialiser.serialise(value);
            }
        }
    }
    GIVEN("A boost::dynamic_bitset holding a value larger than 64-bit")
    {
        std::array<std::uint64_t, 4> actualValues = {
            0x76543210FEDCBA98,
            0xBA9876543210FEDC,
            0x3210FEDCBA987654,
            0xFEDCBA9876543210,
        };

        auto const numBits = actualValues.size() * sizeof(std::uint64_t) * 8;
        auto const value = BitsetType(actualValues.begin(), actualValues.end());

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), isTextual()).WillOnce(Return(false));
            EXPECT_CALL(serialiser.writer(), beginSequence(std::optional(numBits))).Times(1);
            for (std::size_t i = 0uz; i < actualValues.size(); ++i)
            {
                EXPECT_CALL(serialiser.writer(), write(Matcher<std::uint64_t>(Eq(actualValues[i])))).Times(1);
            }
            EXPECT_CALL(serialiser.writer(), endSequence()).Times(1);

            WHEN("Serialising the boost::dynamic_bitset")
            {
                serialiser.serialise(value);
            }
        }
    }
}

TEST_CASE("Verify deserialisation of boost::dynamic_bitset", "[morpheus.serialisation.boost.dynamic_bitset.deserialise]")
{
    GIVEN("Expected contents of a boost::dynamic_bitset holding a 64-bit value with a textual reader")
    {
        constexpr std::uint64_t actualValue = 0xFEDCBA9876543210;
        auto const expectedStringValue = toBitString(std::vector{actualValue});

        THEN("Expect the following sequence of operations on the underlying reader")
        {
            InSequence seq;
            MockedReadSerialiser<true> serialiser;
            EXPECT_CALL(serialiser.reader(), read(An<std::string>())).WillOnce(Return(expectedStringValue));
            WHEN("Deserialising the boost::dynamic_bitset")
            {
                auto const bitset = serialiser.deserialise<BitsetType>();
                REQUIRE(toString(bitset) == expectedStringValue);
            }
        }
    }
    GIVEN("Expected contents of a boost::dynamic_bitset holding a value larger than 64-bit with a non-textual reader")
    {
        std::array<std::uint64_t, 4> actualValues = {
            0x76543210FEDCBA98,
            0xBA9876543210FEDC,
            0x3210FEDCBA987654,
            0xFEDCBA9876543210,
        };

        auto const numBits = actualValues.size() * sizeof(std::uint64_t) * 8;
        auto const value = BitsetType(actualValues.begin(), actualValues.end());

        THEN("Expect the following sequence of operations on the underlying reader")
        {
            InSequence seq;
            MockedReadSerialiser<false> serialiser;
            EXPECT_CALL(serialiser.reader(), beginSequence()).WillOnce(Return(std::optional(numBits)));
            for (std::size_t i = 0uz; i < actualValues.size(); ++i)
            {
                EXPECT_CALL(serialiser.reader(), read(An<std::uint64_t>())).WillOnce(Return(actualValues[i]));
            }
            EXPECT_CALL(serialiser.reader(), endSequence()).Times(1);

            WHEN("Deserialising the boost::dynamic_bitset")
            {
                auto const bitset = serialiser.deserialise<BitsetType>();
                REQUIRE(toString(bitset) == toBitString(actualValues));
            }
        }
    }
}

} // namespace morpheus::serialisation
