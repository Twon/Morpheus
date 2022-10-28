#include "morpheus/core/serialisation/adapters/std/tuple.hpp"
#include "morpheus/core/serialisation/mock/writer.hpp"
#include "morpheus/core/serialisation/mock/serialisers.hpp"

#include <catch2/catch_all.hpp>
#include <gmock/gmock.h>

#include <tuple>

namespace morpheus::serialisation
{

using namespace ::testing;

TEST_CASE("Verify serialisation of std::tuple", "[morpheus.serialisation.tuple.serialise]")
{
    GIVEN("A serialiser which can track expected calls")
    {
        using namespace std::literals::string_view_literals;
        constexpr auto firstValue = "value"sv;
        constexpr std::int64_t secondValue = 10;
        constexpr bool thirdValue = true;
        constexpr double fourthValue = 1.0;

        MockWriteSerialiser serialiser;
        std::tuple value{ firstValue, secondValue, thirdValue, fourthValue };

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            EXPECT_CALL(serialiser.writer(), beginSequence(std::optional<std::size_t>(4))).Times(1);
            EXPECT_CALL(serialiser.writer(), write(firstValue)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<std::int64_t>(Eq(secondValue)))).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<bool>(Eq(thirdValue)))).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<double>(Eq(fourthValue)))).Times(1);
            EXPECT_CALL(serialiser.writer(), endSequence()).Times(1);

            WHEN("Serialising a std::tuple")
            {
                serialiser.serialise(value);
            }
        }
    }
}

} // morpheus::serialisation