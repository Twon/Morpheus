#include "morpheus/core/conformance/value_types.hpp"
#include "morpheus/core/serialisation/adapters/std/indirect.hpp"
#include "morpheus/core/serialisation/mock/reader.hpp"
#include "morpheus/core/serialisation/mock/serialisers.hpp"
#include "morpheus/core/serialisation/mock/writer.hpp"
#include "morpheus/core/serialisation/read_serialiser.hpp"
#include "morpheus/core/serialisation/write_serialiser.hpp"

#include <catch2/catch_test_macros.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <string>
#include <string_view>

namespace morpheus::serialisation
{

using namespace ::testing;
using namespace std::literals::string_view_literals;

TEST_CASE("Verify serialisation of std::indirect", "[morpheus.serialisation.indirect.serialise]")
{
    GIVEN("A std::indirect holding a value")
    {
        constexpr std::int64_t actualValue = 10;
        auto const value = conf::vt::indirect<std::int64_t>(actualValue);

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), beginComposite()).Times(1);
            EXPECT_CALL(serialiser.writer(), beginValue("value"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<std::int64_t>(Eq(actualValue)))).Times(1);
            EXPECT_CALL(serialiser.writer(), endValue()).Times(1);
            EXPECT_CALL(serialiser.writer(), endComposite()).Times(1);

            WHEN("Serialising the std::indirect")
            {
                serialiser.serialise(value);
            }
        }
    }
}

TEST_CASE("Verify deserialisation of std::indirect", "[morpheus.serialisation.indirect.deserialise]")
{
    GIVEN("Expected contents of a std::indirect holding a value")
    {
        constexpr std::int64_t actualValue = 10;

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedReadSerialiser<> serialiser;
            EXPECT_CALL(serialiser.reader(), beginComposite()).Times(1);
            EXPECT_CALL(serialiser.reader(), beginValue("value"sv)).Times(1);
            EXPECT_CALL(serialiser.reader(), read(An<std::int64_t>())).WillOnce(Return(actualValue));
            EXPECT_CALL(serialiser.reader(), endValue()).Times(1);
            EXPECT_CALL(serialiser.reader(), endComposite()).Times(1);
            WHEN("Deserialising the std::indirect")
            {
                using IndirectType = conf::vt::indirect<std::int64_t>;
                auto const expected = serialiser.deserialise<IndirectType>();
                REQUIRE(*expected == actualValue);
            }
        }
    }
}

} // namespace morpheus::serialisation
