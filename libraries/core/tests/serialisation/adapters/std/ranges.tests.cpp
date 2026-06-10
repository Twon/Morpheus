#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/core/serialisation/adapters/std/array.hpp"
#include "morpheus/core/serialisation/adapters/std/deque.hpp"
#include "morpheus/core/serialisation/adapters/std/forward_list.hpp"
#include "morpheus/core/serialisation/adapters/std/list.hpp"
#include "morpheus/core/serialisation/adapters/std/ranges.hpp"
#include "morpheus/core/serialisation/adapters/std/set.hpp"
#include "morpheus/core/serialisation/adapters/std/unordered_set.hpp"
#include "morpheus/core/serialisation/adapters/std/vector.hpp"
// #include "morpheus/core/serialisation/mock/reader.hpp"
#include "morpheus/core/serialisation/mock/serialisers.hpp"
#include "morpheus/core/serialisation/mock/writer.hpp"
#include "morpheus/core/serialisation/write_serialiser.hpp"

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <list>
#include <optional>
#include <set>
#include <string_view>
#include <unordered_set>
#include <vector>

namespace morpheus::serialisation
{

using namespace ::testing;
using namespace std::literals::string_view_literals;

TEMPLATE_TEST_CASE("Verify serialisation of sequence containers std::ranges",
                   "[morpheus.serialisation.ranges.serialise.sequence_containers]",
                   (std::array<int, 5>),
                   std::deque<int>,
                   std::list<int>,
                   std::set<int>,
                   std::unordered_set<int>,
                   std::vector<int>)
{
    GIVEN("A range of values")
    {
        TestType container{1, 2, 3, 4, 5};

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), beginSequence(std::optional(conf::ranges::size(container)))).Times(1);
            conf::ranges::for_each(container,
                                   [&serialiser](auto const& element) { EXPECT_CALL(serialiser.writer(), write(Matcher<int>(Eq(element)))).Times(1); });
            EXPECT_CALL(serialiser.writer(), endSequence()).Times(1);

            WHEN("Serialising the std::expected")
            {
                serialiser.serialise(container);
            }
        }
    }
}

TEST_CASE("Verify deserialisation of sequence containers std::ranges", "[morpheus.serialisation.ranges.deserialise.sequence_containers]")
{
    GIVEN("A sequence of values in the reader")
    {
        std::vector<int> const expectedValues{1, 2, 3, 4, 5};

        THEN("Expect the following sequence of operations on the underlying reader")
        {
            InSequence seq;
            MockedReadSerialiser<> serialiser;

            EXPECT_CALL(serialiser.reader(), beginSequence()).WillOnce(Return(std::optional<std::size_t>(expectedValues.size())));
            for (auto const& value : expectedValues)
            {
                EXPECT_CALL(serialiser.reader(), read(Matcher<int>(_))).WillOnce(Return(value));
            }
            EXPECT_CALL(serialiser.reader(), endSequence()).Times(1);

            WHEN("Deserialising the range")
            {
                auto const actualValues = serialiser.deserialise<std::vector<int>>();
                REQUIRE(actualValues == expectedValues);
            }
        }
    }
}

TEST_CASE("Verify optimized block-read deserialisation of byte sequence containers",
          "[morpheus.serialisation.ranges.deserialise.byte_sequence_containers.binary]")
{
    GIVEN("A sequence of bytes in the reader")
    {
        std::vector<std::byte> const expectedValues{std::byte{1}, std::byte{2}, std::byte{3}};

        THEN("Expect a single block-read on the underlying reader instead of multiple byte-reads")
        {
            InSequence seq;
            MockedReadSerialiser<false> serialiser;

            EXPECT_CALL(serialiser.reader(), beginSequence()).WillOnce(Return(std::optional<std::size_t>(expectedValues.size())));
            EXPECT_CALL(serialiser.reader(), read(Matcher<std::byte>(_))).WillOnce(Return(expectedValues[0]));
            EXPECT_CALL(serialiser.reader(), read(Matcher<std::byte>(_))).WillOnce(Return(expectedValues[1]));
            EXPECT_CALL(serialiser.reader(), read(Matcher<std::byte>(_))).WillOnce(Return(expectedValues[2]));
            EXPECT_CALL(serialiser.reader(), endSequence()).Times(1);

            WHEN("Deserialising a std::list<std::byte>")
            {
                auto const actualValues = serialiser.deserialise<std::list<std::byte>>();
                std::vector<std::byte> const actualVec(actualValues.begin(), actualValues.end());
                REQUIRE(actualVec == expectedValues);
            }
        }
    }
}

TEST_CASE("Verify optimized block-read deserialisation of byte sequence containers",
          "[morpheus.serialisation.ranges.deserialise.byte_sequence_containers.text]")
{
    GIVEN("A sequence of bytes in the reader")
    {
        std::vector<std::byte> const expectedValues{std::byte{1}, std::byte{2}, std::byte{3}};

        THEN("Expect a single block-read on the underlying reader instead of multiple byte-reads")
        {
            InSequence seq;
            MockedReadSerialiser<true> serialiser;

            EXPECT_CALL(serialiser.reader(), read(Matcher<std::vector<std::byte>>(_))).WillOnce(Return(expectedValues));

            WHEN("Deserialising a std::list<std::byte>")
            {
                auto const actualValues = serialiser.deserialise<std::vector<std::byte>>();
                REQUIRE(actualValues == expectedValues);
            }
        }
    }
}

} // namespace morpheus::serialisation
