#include "morpheus/core/serialisation/adapters/std/tuple.hpp"
#include "morpheus/core/serialisation/mock/reader.hpp"
#include "morpheus/core/serialisation/mock/serialisers.hpp"
#include "morpheus/core/serialisation/mock/writer.hpp"

#include <catch2/catch_test_macros.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string_view>
#include <string>
#include <tuple>
#include <utility>

namespace morpheus::serialisation
{

using namespace ::testing;

TEST_CASE("Verify serialisation of std::tuple", "[morpheus.serialisation.tuple.serialise]")
{
    GIVEN("A std::tuple holding a value")
    {
        using namespace std::literals::string_view_literals;
        constexpr auto firstValue = "value"sv;
        constexpr std::int64_t secondValue = 10;
        constexpr bool thirdValue = true;
        constexpr double fourthValue = 1.0;
        std::tuple value{ firstValue, secondValue, thirdValue, fourthValue };

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), beginSequence(std::optional<std::size_t>(4))).Times(1);
            EXPECT_CALL(serialiser.writer(), write(firstValue)).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<std::int64_t>(Eq(secondValue)))).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<bool>(Eq(thirdValue)))).Times(1);
            EXPECT_CALL(serialiser.writer(), write(Matcher<double>(Eq(fourthValue)))).Times(1);
            EXPECT_CALL(serialiser.writer(), endSequence()).Times(1);

            WHEN("Serialising a std::tuple")
            {
                serialiser.serialise(value);
            }
        }
    }
}

TEST_CASE("Verify deserialisation of std::tuple", "[morpheus.serialisation.tuple.deserialise]")
{
    GIVEN("A serialiser which can track expected calls")
    {
        using namespace std::literals::string_literals;
        using ExpectedTuple = std::tuple<std::string, std::int64_t,  bool, double>;
        const ExpectedTuple expectedValues( "value"s, 10, true, 1.0 );

        THEN("Expect the following sequence of operations on the underlying reader")
        {
            MockedReadSerialiser serialiser;
            EXPECT_CALL(serialiser.reader(), beginSequence()).WillOnce(Return(std::optional<std::size_t>(std::tuple_size<ExpectedTuple>::value)));

            [&] <std::size_t... Index>(std::index_sequence<Index...>)
            {
                (EXPECT_CALL(serialiser.reader(), read(An< std::tuple_element_t<Index, ExpectedTuple>>())).WillOnce(Return(std::get<Index>(expectedValues))), ...);
            }(std::make_index_sequence<std::tuple_size<ExpectedTuple>::value>());

            EXPECT_CALL(serialiser.reader(), endSequence()).Times(1);

            WHEN("Deserialising a std::pair")
            {
                auto const value = serialiser.deserialise<ExpectedTuple>();
                REQUIRE(std::get<0>(value) == std::get<0>(expectedValues));
                REQUIRE(std::get<1>(value) == std::get<1>(expectedValues));
                REQUIRE(std::get<2>(value) == std::get<2>(expectedValues));
                REQUIRE(std::get<3>(value) == std::get<3>(expectedValues));
            }
        }
    }
}

} // morpheus::serialisation
