#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/core/serialisation/adapters/std/bitset.hpp"
#include "morpheus/core/serialisation/mock/reader.hpp"
#include "morpheus/core/serialisation/mock/serialisers.hpp"
#include "morpheus/core/serialisation/mock/writer.hpp"
#include "morpheus/core/serialisation/read_serialiser.hpp"
#include "morpheus/core/serialisation/write_serialiser.hpp"

#include <catch2/catch_test_macros.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <bitset>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace morpheus::serialisation
{

using namespace ::testing;
using namespace std::literals::string_view_literals;

std::string toBitString(conf::ranges::range auto const& values)
{
    std::string result;
    result.reserve(std::size(values) * 64uz);

    for (auto v : conf::ranges::reverse_view(values))
        result += std::bitset<64>(v).to_string();

    return result;
}

TEST_CASE("Verify serialisation of std::bitset", "[morpheus.serialisation.bitset.serialise]")
{
    GIVEN("A std::bitset holding a 64-bit value")
    {
        constexpr std::uint64_t actualValue = 0xFEDCBA9876543210;
        auto const expectedStringValue = toBitString(std::vector{actualValue});
        auto const value = std::bitset<64>(actualValue);

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), isTextual()).WillOnce(Return(true));
            EXPECT_CALL(serialiser.writer(), write(Matcher<std::string_view>(Eq(expectedStringValue)))).Times(1);

            WHEN("Serialising the std::bitset")
            {
                serialiser.serialise(value);
            }
        }
    }
    GIVEN("A std::bitset holding a 64-bit value")
    {
        constexpr std::uint64_t actualValue = 0xFEDCBA9876543210;
        auto const value = std::bitset<64>(actualValue);

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), isTextual()).WillOnce(Return(false));
            EXPECT_CALL(serialiser.writer(), write(Matcher<std::uint64_t>(Eq(actualValue)))).Times(1);

            WHEN("Serialising the std::bitset")
            {
                serialiser.serialise(value);
            }
        }
    }
    GIVEN("A std::bitset holding a value larger than 64-bit")
    {
        std::array<std::uint64_t, 4> actualValues = {
            0x76543210FEDCBA98,
            0xBA9876543210FEDC,
            0x3210FEDCBA987654,
            0xFEDCBA9876543210,
        };

        auto const value = std::bitset<256>(toBitString(actualValues));

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), isTextual()).WillOnce(Return(false));
            EXPECT_CALL(serialiser.writer(), beginSequence(std::optional(value.size()))).Times(1);
            for (std::size_t i = 0uz; i < actualValues.size(); ++i)
            {
                EXPECT_CALL(serialiser.writer(), write(Matcher<std::uint64_t>(Eq(actualValues[i])))).Times(1);
            }
            EXPECT_CALL(serialiser.writer(), endSequence()).Times(1);

            WHEN("Serialising the std::bitset")
            {
                serialiser.serialise(value);
            }
        }
    }
}

TEST_CASE("Verify deserialisation of std::bitset", "[morpheus.serialisation.bitset.deserialise]")
{
    GIVEN("Expected contents of a std::bitset holding a 64-bit value with a textual reader")
    {
        constexpr std::uint64_t actualValue = 0xFEDCBA9876543210;
        auto const expectedStringValue = toBitString(std::vector{actualValue});

        THEN("Expect the following sequence of operations on the underlying reader")
        {
            InSequence seq;
            MockedReadSerialiser<true> serialiser;
            EXPECT_CALL(serialiser.reader(), read(An<std::string>())).WillOnce(Return(expectedStringValue));
            WHEN("Deserialising the std::bitset")
            {
                using BitsetType = std::bitset<64>;
                auto const bitset = serialiser.deserialise<BitsetType>();
                REQUIRE(bitset.to_string() == expectedStringValue);
            }
        }
    }
    GIVEN("Expected contents of a std::bitset holding a 64-bit value with a non-textual reader")
    {
        constexpr std::uint64_t actualValue = 0xFEDCBA9876543210;

        THEN("Expect the following sequence of operations on the underlying reader")
        {
            InSequence seq;
            MockedReadSerialiser<false> serialiser;
            EXPECT_CALL(serialiser.reader(), read(An<std::uint64_t>())).WillOnce(Return(actualValue));
            WHEN("Deserialising the std::bitset")
            {
                using BitsetType = std::bitset<64>;
                auto const bitset = serialiser.deserialise<BitsetType>();
                REQUIRE(bitset.to_ullong() == actualValue);
            }
        }
    }
    GIVEN("Expected contents of a std::bitset holding a value larger than 64-bit with a non-textual reader")
    {
        std::array<std::uint64_t, 4> actualValues = {
            0x76543210FEDCBA98,
            0xBA9876543210FEDC,
            0x3210FEDCBA987654,
            0xFEDCBA9876543210,
        };

        auto const value = std::bitset<256>(toBitString(actualValues));

        THEN("Expect the following sequence of operations on the underlying reader")
        {
            InSequence seq;
            MockedReadSerialiser<false> serialiser;
            EXPECT_CALL(serialiser.reader(), beginSequence()).WillOnce(Return(std::optional(actualValues.size())));
            for (std::size_t i = 0uz; i < actualValues.size(); ++i)
            {
                EXPECT_CALL(serialiser.reader(), read(An<std::uint64_t>())).WillOnce(Return(actualValues[i]));
            }
            EXPECT_CALL(serialiser.reader(), endSequence()).Times(1);

            WHEN("Deserialising the std::bitset")
            {
                using BitsetType = std::bitset<256>;
                auto const bitset = serialiser.deserialise<BitsetType>();
                REQUIRE(bitset.to_string() == toBitString(actualValues));
            }
        }
    }
}

} // namespace morpheus::serialisation
