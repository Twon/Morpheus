#include "morpheus/core/serialisation/adapters/std/pair.hpp"
#include "morpheus/core/serialisation/mock/writer.hpp"
#include "morpheus/core/serialisation/mock/serialisers.hpp"

#include <catch2/catch_all.hpp>
#include <gmock/gmock.h>

#include <utility>

namespace morpheus::serialisation
{

using namespace ::testing;

TEST_CASE("Verify serialisation of std::pair", "[morpheus.serialisation.pair.serialise]")
{
    GIVEN("A std::pair holding a value")
    {
        using namespace std::literals::string_view_literals;
        constexpr auto firstValue = "value"sv;
        constexpr std::int64_t secondValue = 10;
        std::pair value{ firstValue, secondValue };

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), beginSequence(std::optional<std::size_t>(2))).Times(1);
            EXPECT_CALL(serialiser.writer(), write(firstValue)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<std::int64_t>(Eq(secondValue)))).Times(1);
            EXPECT_CALL(serialiser.writer(), endSequence()).Times(1);

            WHEN("Serialising a std::pair")
            {
                serialiser.serialise(value);
            }
        }
    }
}

TEST_CASE("Verify deserialisation of std::pair", "[morpheus.serialisation.pair.deserialise]")
{
    GIVEN("A serialiser which can track expected calls")
    {
        using namespace std::literals::string_view_literals;
        constexpr auto firstValue = true;
        constexpr std::int64_t secondValue = 10;

        THEN("Expect the following sequence of operations on the underlying reader")
        {
            MockedReadSerialiser serialiser;
            EXPECT_CALL(serialiser.reader(), beginSequence()).WillOnce(Return(std::optional<std::size_t>(2)));
            EXPECT_CALL(serialiser.reader(), read(An<bool>())).WillOnce(Return(firstValue));
            EXPECT_CALL(serialiser.reader(), read(An<std::int64_t>())).WillOnce(Return(secondValue));
            EXPECT_CALL(serialiser.reader(), endSequence()).Times(1);

            WHEN("Deserialising a std::pair")
            {
                using ExpectedPair = std::pair<bool, std::int64_t>;
                auto const value = serialiser.deserialise<ExpectedPair>();
                REQUIRE(value.first == firstValue);
                REQUIRE(value.second == secondValue);
            }
        }
    }
}

} // morpheus::serialisation