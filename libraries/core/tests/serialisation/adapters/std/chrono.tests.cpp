#include "morpheus/core/conformance/date.hpp"
#include "morpheus/core/serialisation/adapters/std/chrono.hpp"
#include "morpheus/core/serialisation/mock/reader.hpp"
#include "morpheus/core/serialisation/mock/serialisers.hpp"
#include "morpheus/core/serialisation/mock/writer.hpp"

#include <catch2/catch_all.hpp>
#include <gmock/gmock.h>

#include <chrono>
#include <string>
#include <string_view>

namespace morpheus::serialisation
{

using namespace ::testing;
using namespace std::literals::string_view_literals;

TEST_CASE("Verify serialisation of std::chrono::duration", "[morpheus.serialisation.chrono.duration.serialise]")
{
    GIVEN("A std::chrono::duration when outputting to text")
    {
        auto const value = std::chrono::days{7};

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), isTextual()).WillOnce(Return(true));
            EXPECT_CALL(serialiser.writer(), write(Matcher<std::string_view>(Eq("7d")))).Times(1);
            
            WHEN("Serialising the std::expected") { serialiser.serialise(value); }
        }
    }
    GIVEN("An std::chrono::duration when outputting not outputting to text")
    {
        auto const value = std::chrono::days{7};

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), isTextual()).WillOnce(Return(false));
            EXPECT_CALL(serialiser.writer(), write(Matcher<std::chrono::days::rep>(Eq(value.count())))).Times(1);

            WHEN("Serialising the std::expected") { serialiser.serialise(value); }
        }
    }
}

TEST_CASE("Verify deserialisation of std::chrono::duration", "[morpheus.serialisation.chrono.duration.deserialise]")
{
    GIVEN("Expected contents of a std::chrono::duration holding a value")
    {
        auto const actualValue = std::chrono::days{7};

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedReadSerialiser serialiser;
            EXPECT_CALL(serialiser.reader(), isTextual()).WillOnce(Return(true));
            EXPECT_CALL(serialiser.reader(), read(An<std::string>())).WillOnce(Return("7d"));

            WHEN("Deserialising the std::chrono::duration")
            {
                auto const expected = serialiser.deserialise<std::chrono::days>();
                REQUIRE(expected == actualValue);
            }
        }
    }
    GIVEN("Expected contents of a std::expected holding an error")
    {
        auto const actualValue = std::chrono::days{7};

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedReadSerialiser serialiser;
            EXPECT_CALL(serialiser.reader(), isTextual()).WillOnce(Return(false));
            EXPECT_CALL(serialiser.reader(), read(An<std::chrono::days::rep>())).WillOnce(Return(actualValue.count()));

            WHEN("Deserialising the std::chrono::duration")
            {
                auto const expected = serialiser.deserialise<std::chrono::days>();
                REQUIRE(expected == actualValue);
            }
        }
    }
}

} // namespace morpheus::serialisation