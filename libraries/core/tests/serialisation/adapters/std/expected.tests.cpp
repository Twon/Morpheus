#include "morpheus/core/conformance/expected.hpp"
#include "morpheus/core/serialisation/adapters/std/expected.hpp"
#include "morpheus/core/serialisation/mock/reader.hpp"
#include "morpheus/core/serialisation/mock/serialisers.hpp"
#include "morpheus/core/serialisation/mock/writer.hpp"

#include <catch2/catch_all.hpp>
#include <gmock/gmock.h>

#include <string>
#include <string_view>

namespace morpheus::serialisation
{

using namespace ::testing;
using namespace std::literals::string_view_literals;

TEST_CASE("Verify serialisation of std::expected", "[morpheus.serialisation.expected.serialise]")
{
    GIVEN("A std::expected holding a value")
    {
        constexpr std::int64_t actualValue = 10;
        auto const value = exp_ns::expected<std::int64_t, std::string>(actualValue);

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), beginComposite()).Times(1);
            EXPECT_CALL(serialiser.writer(), beginValue("state"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<bool>(Eq(true)))).Times(1);
            EXPECT_CALL(serialiser.writer(), endValue()).Times(1);
            EXPECT_CALL(serialiser.writer(), beginValue("value"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<std::int64_t>(Eq(actualValue)))).Times(1);
            EXPECT_CALL(serialiser.writer(), endValue()).Times(1);
            EXPECT_CALL(serialiser.writer(), endComposite()).Times(1);

            WHEN("Serialising the std::expected") { serialiser.serialise(value); }
        }
    }
    GIVEN("An std::expected holding an error")
    {
        std::string const actualValue = "This string is an error";
        auto const value = exp_ns::expected<std::int64_t, std::string>(exp_ns::unexpected(actualValue));

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), beginComposite()).Times(1);
            EXPECT_CALL(serialiser.writer(), beginValue("state"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<bool>(Eq(false)))).Times(1);
            EXPECT_CALL(serialiser.writer(), endValue()).Times(1);
            EXPECT_CALL(serialiser.writer(), beginValue("error"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<std::string_view>(Eq(actualValue)))).Times(1);
            EXPECT_CALL(serialiser.writer(), endValue()).Times(1);
            EXPECT_CALL(serialiser.writer(), endComposite()).Times(1);

            WHEN("Serialising the std::expected") { serialiser.serialise(value); }
        }
    }
}

TEST_CASE("Verify deserialisation of std::expected", "[morpheus.serialisation.expected.deserialise]")
{
    GIVEN("Expected contents of a std::expected holding a value")
    {
        constexpr std::int64_t actualValue = 10;

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedReadSerialiser serialiser;
            EXPECT_CALL(serialiser.reader(), beginComposite()).Times(1);
            EXPECT_CALL(serialiser.reader(), beginValue("state"sv)).Times(1);
            EXPECT_CALL(serialiser.reader(), read(An<bool>())).WillOnce(Return(true));
            EXPECT_CALL(serialiser.reader(), endValue()).Times(1);
            EXPECT_CALL(serialiser.reader(), beginValue("value"sv)).Times(1);
            EXPECT_CALL(serialiser.reader(), read(An<std::int64_t>())).WillOnce(Return(actualValue));
            EXPECT_CALL(serialiser.reader(), endValue()).Times(1);
            EXPECT_CALL(serialiser.reader(), endComposite()).Times(1);
            WHEN("Serialising the std::expected")
            {
                using ExpectedType = exp_ns::expected<std::int64_t, std::string>;
                auto const expected = serialiser.deserialise<ExpectedType>();
                REQUIRE(expected.value() == actualValue);
            }
        }
    }
    GIVEN("Expected contents of a std::expected holding an error")
    {
        std::string const actualValue = "This string is an error";

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedReadSerialiser serialiser;
            EXPECT_CALL(serialiser.reader(), beginComposite()).Times(1);
            EXPECT_CALL(serialiser.reader(), beginValue("state"sv)).Times(1);
            EXPECT_CALL(serialiser.reader(), read(An<bool>())).WillOnce(Return(false));
            EXPECT_CALL(serialiser.reader(), endValue()).Times(1);
            EXPECT_CALL(serialiser.reader(), beginValue("error"sv)).Times(1);
            EXPECT_CALL(serialiser.reader(), read(An<std::string>())).WillOnce(Return(actualValue));
            EXPECT_CALL(serialiser.reader(), endValue()).Times(1);
            EXPECT_CALL(serialiser.reader(), endComposite()).Times(1);

            WHEN("Deserialising the std::expected")
            {
                using ExpectedType = std::expected<std::int64_t, std::string>;
                auto const expected = serialiser.deserialise<ExpectedType>();
                REQUIRE(expected.error() == actualValue);
            }
        }
    }
}

} // namespace morpheus::serialisation