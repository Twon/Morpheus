#include "morpheus/core/serialisation/adapters/std/reference_wrapper.hpp"
#include "morpheus/core/serialisation/mock/serialisers.hpp"
#include "morpheus/core/serialisation/mock/writer.hpp"

#include <catch2/catch_all.hpp>
#include <gmock/gmock.h>

#include <functional>

namespace morpheus::serialisation
{

using namespace ::testing;

TEST_CASE("Verify serialisation of std::reference_wrapper", "[morpheus.serialisation.reference_wrapper.serialise]")
{
    GIVEN("A std::reference_wrapper holding a value")
    {
        using namespace std::literals::string_view_literals;
        constexpr std::int64_t expectedValue = 10;
        std::reference_wrapper value{expectedValue};

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), write(Matcher<std::int64_t>(Eq(expectedValue)))).Times(1);

            WHEN("Serialising a std::reference_wrapper")
            {
                serialiser.serialise(value);
            }
        }
    }
}

TEST_CASE("Verify deserialisation of std::reference_wrapper", "[morpheus.serialisation.reference_wrapper.deserialise]")
{
    GIVEN("A serialiser which can track expected calls")
    {
        constexpr std::int64_t expectedValue = 10;

        THEN("Expect the following sequence of operations on the underlying reader")
        {
            MockedReadSerialiser<> serialiser;
            EXPECT_CALL(serialiser.reader(), read(An<std::int64_t>())).WillOnce(Return(expectedValue));

            WHEN("Deserialising a std::reference_wrapper")
            {
                std::int64_t valueHolder = 0;
                std::reference_wrapper<std::int64_t> value{valueHolder};
                serialiser.deserialise(value);
                REQUIRE(value.get() == expectedValue);
            }
        }
    }
}

} // namespace morpheus::serialisation
