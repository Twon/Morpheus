#include "morpheus/core/serialisation/adapters/std/variant.hpp"
#include "morpheus/core/serialisation/mock/reader.hpp"
#include "morpheus/core/serialisation/mock/serialisers.hpp"
#include "morpheus/core/serialisation/mock/writer.hpp"

#include <catch2/catch_test_macros.hpp>
#include <gmock/gmock.h>

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <variant>

namespace morpheus::serialisation
{

using namespace ::testing;
using namespace std::literals::string_view_literals;

TEST_CASE("Verify serialisation of std::variant", "[morpheus.serialisation.variant.serialise]")
{
    GIVEN("A std::variant holding a value")
    {
        constexpr bool actualValue = true;
        auto const value = std::variant<int, bool, std::string>(actualValue);

        THEN("Expect the following sequence of operations on the underlying writer when serialising to text")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), beginComposite()).Times(1);
            EXPECT_CALL(serialiser.writer(), isTextual()).WillOnce(Return(true));
            EXPECT_CALL(serialiser.writer(), beginValue("type"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), write("bool"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), endValue()).Times(1);
            EXPECT_CALL(serialiser.writer(), beginValue("value"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<bool>(Eq(actualValue)))).Times(1);
            EXPECT_CALL(serialiser.writer(), endValue()).Times(1);
            EXPECT_CALL(serialiser.writer(), endComposite()).Times(1);

            WHEN("Serialising the std::variant")
            {
                serialiser.serialise(value);
            }
        }
    }
    GIVEN("An default constructed std::variant")
    {
        auto const value = std::variant<int, bool, std::string>();

        THEN("Expect the following sequence of operations on the underlying writer when serialising to text")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), beginComposite()).Times(1);
            EXPECT_CALL(serialiser.writer(), isTextual()).WillOnce(Return(true));
            EXPECT_CALL(serialiser.writer(), beginValue("type"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), write("int"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), endValue()).Times(1);
            EXPECT_CALL(serialiser.writer(), beginValue("value"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<int>(Eq(int{})))).Times(1);
            EXPECT_CALL(serialiser.writer(), endValue()).Times(1);
            EXPECT_CALL(serialiser.writer(), endComposite()).Times(1);

            WHEN("Serialising the std::variant")
            {
                serialiser.serialise(value);
            }
        }
    }
    GIVEN("A std::variant holding a value when serialising to binary")
    {
        constexpr bool actualValue = true;
        auto const value = std::variant<int, bool, std::string>(actualValue);

        THEN("Expect the following sequence of operations on the underlying writer when serialising to text")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), beginComposite()).Times(1);
            EXPECT_CALL(serialiser.writer(), isTextual()).WillOnce(Return(false));
            EXPECT_CALL(serialiser.writer(), beginValue("index"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<std::uint64_t>(Eq(value.index())))).Times(1);
            EXPECT_CALL(serialiser.writer(), endValue()).Times(1);
            EXPECT_CALL(serialiser.writer(), beginValue("value"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<bool>(Eq(actualValue)))).Times(1);
            EXPECT_CALL(serialiser.writer(), endValue()).Times(1);
            EXPECT_CALL(serialiser.writer(), endComposite()).Times(1);

            WHEN("Serialising the std::variant")
            {
                serialiser.serialise(value);
            }
        }
    }
    GIVEN("An default constructed std::variant")
    {
        auto const value = std::variant<int, bool, std::string>();

        THEN("Expect the following sequence of operations on the underlying writer when serialising to text")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), beginComposite()).Times(1);
            EXPECT_CALL(serialiser.writer(), isTextual()).WillOnce(Return(false));
            EXPECT_CALL(serialiser.writer(), beginValue("index"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<std::uint64_t>(Eq(value.index())))).Times(1);
            EXPECT_CALL(serialiser.writer(), endValue()).Times(1);
            EXPECT_CALL(serialiser.writer(), beginValue("value"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<int>(Eq(int{})))).Times(1);
            EXPECT_CALL(serialiser.writer(), endValue()).Times(1);
            EXPECT_CALL(serialiser.writer(), endComposite()).Times(1);

            WHEN("Serialising the std::variant")
            {
                serialiser.serialise(value);
            }
        }
    }
}

} // morpheus::serialisation
