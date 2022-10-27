#include "morpheus/core/serialisation/adapters/std/unique_ptr.hpp"
#include "morpheus/core/serialisation/mock_writer.hpp"
#include "morpheus/core/serialisation/mock_serialisers.hpp"

#include <catch2/catch_all.hpp>
#include <gmock/gmock.h>

#include <memory>

namespace morpheus::serialisation
{

using namespace ::testing;

TEST_CASE("Verify serialisation of std::unique_ptr", "[morpheus.serialisation.unique_ptr.serialise]")
{
    GIVEN("A std::unique_ptr holding a value")
    {
        constexpr std::int64_t actualValue = 10;
        auto const value = std::make_unique<decltype(actualValue)>(actualValue);

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            MockWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), beginNullable(false)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<std::int64_t>(Eq(actualValue)))).Times(1);
            EXPECT_CALL(serialiser.writer(), endNullable()).Times(1);

            WHEN("Serialising the std::unique_ptr")
            {
                serialiser.serialise(value);
            }
        }
    }
    GIVEN("An empty std::unique_ptr")
    {
        auto const value = std::unique_ptr<std::int64_t>();

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            MockWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), beginNullable(true)).Times(1);
            EXPECT_CALL(serialiser.writer(), endNullable()).Times(1);

            WHEN("Serialising the std::unique_ptr")
            {
                serialiser.serialise(value);
            }
        }
    }
}

} // morpheus::serialisation