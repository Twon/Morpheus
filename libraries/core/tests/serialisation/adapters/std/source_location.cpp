#include "morpheus/core/conformance/source_location.hpp"
#include "morpheus/core/serialisation/adapters/std/source_location.hpp"
#include "morpheus/core/serialisation/mock/serialisers.hpp"
#include "morpheus/core/serialisation/mock/writer.hpp"
#include "morpheus/core/serialisation/write_serialiser.hpp"

#include <catch2/catch_test_macros.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <string_view>

namespace morpheus::serialisation
{

using namespace ::testing;
using namespace std::literals::string_view_literals;

TEST_CASE("Verify serialisation of std::source_location", "[morpheus.serialisation.source_location.serialise]")
{
    GIVEN("A std::source_location holding a value")
    {
        conf::sl::source_location location = MORPHEUS_CURRENT_LOCATION;

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), beginComposite()).Times(1);
            EXPECT_CALL(serialiser.writer(), beginValue("file_name"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<char const*>(Eq(location.file_name())))).Times(1);
            EXPECT_CALL(serialiser.writer(), endValue()).Times(1);
            EXPECT_CALL(serialiser.writer(), beginValue("function_name"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<char const*>(Eq(location.function_name())))).Times(1);
            EXPECT_CALL(serialiser.writer(), endValue()).Times(1);
            EXPECT_CALL(serialiser.writer(), beginValue("line"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<std::uint32_t>(Eq(location.line())))).Times(1);
            EXPECT_CALL(serialiser.writer(), endValue()).Times(1);
            EXPECT_CALL(serialiser.writer(), beginValue("column"sv)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<std::uint32_t>(Eq(location.column())))).Times(1);
            EXPECT_CALL(serialiser.writer(), endValue()).Times(1);
            EXPECT_CALL(serialiser.writer(), endComposite()).Times(1);

            WHEN("Serialising a std::source_location")
            {
                serialiser.serialise(location);
            }
        }
    }
}

} // namespace morpheus::serialisation
