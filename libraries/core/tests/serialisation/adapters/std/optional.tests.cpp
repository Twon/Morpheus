#include "morpheus/core/serialisation/adapters/std/optional.hpp"
#include "morpheus/core/serialisation/mock/reader.hpp"
#include "morpheus/core/serialisation/mock/serialisers.hpp"
#include "morpheus/core/serialisation/mock/writer.hpp"

#include <catch2/catch_all.hpp>
#include <gmock/gmock.h>

#include <optional>
#include <string_view>

namespace morpheus::serialisation
{

using namespace ::testing;

TEST_CASE("Verify serialisation of std::optional", "[morpheus.serialisation.optional.serialise]")
{
    GIVEN("A std::optional holding a value")
    {
        constexpr std::int64_t actualValue = 10;
        auto const value = std::optional<decltype(actualValue)>(actualValue);

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), beginNullable(false)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<std::int64_t>(Eq(actualValue)))).Times(1);
            EXPECT_CALL(serialiser.writer(), endNullable()).Times(1);

            WHEN("Serialising the std::optional")
            {
                serialiser.serialise(value);
            }
        }
    }
    GIVEN("An empty std::optional")
    {
        auto const value = std::optional<std::int64_t>();

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), beginNullable(true)).Times(1);
            EXPECT_CALL(serialiser.writer(), endNullable()).Times(1);

            WHEN("Serialising the std::optional")
            {
                serialiser.serialise(value);
            }
        }
    }
}

TEST_CASE("Verify deserialisation of std::optional", "[morpheus.serialisation.optional.deserialise]")
{
    GIVEN("Expected contents of a std::optional holding a value")
    {
        constexpr std::int64_t actualValue = 10;

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            MockedReadSerialiser serialiser;
            EXPECT_CALL(serialiser.reader(), beginNullable()).WillOnce(Return(false));
            EXPECT_CALL(serialiser.reader(), read(An<std::int64_t>())).WillOnce(Return(actualValue));
            EXPECT_CALL(serialiser.reader(), endNullable()).Times(1);

            WHEN("Serialising the std::unique_ptr")
            {
                using ExpectedType = std::optional<std::int64_t>;
                auto const ptr = serialiser.deserialise<ExpectedType>();
                REQUIRE(*ptr == actualValue);
            }
        }
    }
    GIVEN("Expected contents of empty std::unique_ptr")
    {
        THEN("Expect the following sequence of operations on the underlying writer")
        {
            MockedReadSerialiser serialiser;
            EXPECT_CALL(serialiser.reader(), beginNullable()).WillOnce(Return(true));
            EXPECT_CALL(serialiser.reader(), endNullable()).Times(1);

            WHEN("Deserialising the std::unique_ptr")
            {
                using ExpectedType = std::optional<std::int64_t>;
                auto const ptr = serialiser.deserialise<ExpectedType>();
                REQUIRE(!ptr);
            }
        }
    }
}

} // morpheus::serialisation