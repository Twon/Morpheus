#include "morpheus/core/serialisation/adapters/std/optional.hpp"
#include "morpheus/core/serialisation/mock/reader.hpp"
#include "morpheus/core/serialisation/mock/serialisers.hpp"
#include "morpheus/core/serialisation/mock/writer.hpp"
#include "morpheus/core/serialisation/read_serialiser.hpp"
#include "morpheus/core/serialisation/write_serialiser.hpp"

#include <catch2/catch_test_macros.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <optional>

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

            WHEN("Serialising the std::optional")
            {
                using ExpectedType = std::optional<std::int64_t>;
                auto const optional = serialiser.deserialise<ExpectedType>();
                REQUIRE(*optional == actualValue);
            }
        }
    }
    GIVEN("Expected contents of empty std::optional")
    {
        THEN("Expect the following sequence of operations on the underlying writer")
        {
            MockedReadSerialiser serialiser;
            EXPECT_CALL(serialiser.reader(), beginNullable()).WillOnce(Return(true));
            EXPECT_CALL(serialiser.reader(), endNullable()).Times(1);

            WHEN("Deserialising the std::optional")
            {
                using ExpectedType = std::optional<std::int64_t>;
                auto const optional = serialiser.deserialise<ExpectedType>();
                REQUIRE(!optional);
            }
        }
    }
}

} // namespace morpheus::serialisation
