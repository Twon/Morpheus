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

/*
TEST_CASE("Verify deserialisation of std::ranges", "[morpheus.serialisation.ranges.deserialise]")
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
                using ExpectedType = exp_ns::expected<std::int64_t, std::string>;
                auto const expected = serialiser.deserialise<ExpectedType>();
                REQUIRE(expected.error() == actualValue);
            }
        }
    }
}
*/
} // namespace morpheus::serialisation
