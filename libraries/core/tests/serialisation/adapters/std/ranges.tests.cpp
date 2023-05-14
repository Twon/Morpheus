#include "morpheus/core/meta/concepts/string.hpp"
#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/core/serialisation/adapters/std/array.hpp"
#include "morpheus/core/serialisation/adapters/std/ranges.hpp"
#include "morpheus/core/serialisation/adapters/std/vector.hpp"
#include "morpheus/core/serialisation/mock/reader.hpp"
#include "morpheus/core/serialisation/mock/serialisers.hpp"
#include "morpheus/core/serialisation/mock/writer.hpp"

#include <catch2/catch_all.hpp>
#include <gmock/gmock.h>

#include <initializer_list>
#include <array>
#include <string_view>
#include <utility>
#include <vector>

namespace morpheus::serialisation
{

using namespace ::testing;
using namespace std::literals::string_view_literals;

TEST_CASE("Verify serialisation of ranges", "[morpheus.serialisation.ranges]")
{
    STATIC_REQUIRE(detail::IsRange<std::vector<int>>);
//    STATIC_REQUIRE(detail::IsRange<std::string_view>);
//    STATIC_REQUIRE(meta::IsString<std::string_view>);
    STATIC_REQUIRE(meta::IsStringView<std::string_view>);
}

TEMPLATE_TEST_CASE("Verify serialisation of sequence containers std::ranges", "[morpheus.serialisation.ranges.serialise.sequence_containers]", (std::array<int, 5>), std::vector<int>)
{
    GIVEN("A range of values")
    {
        TestType container([]
        {
            std::initializer_list<int> const values = {1, 2, 3, 4, 5};
            if constexpr (std::is_constructible_v<TestType, decltype(values)>)
            {
                return values; 
            }
            else
            {
                return TestType{1, 2, 3, 4, 5};
            }
        }());

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), beginSequence(std::optional(ranges::size(container)))).Times(1);
            ranges::for_each(container, [&serialiser](auto const& element) { EXPECT_CALL(serialiser.writer(), write(Matcher<int>(Eq(element)))).Times(1); });
            EXPECT_CALL(serialiser.writer(), endSequence()).Times(1);

            WHEN("Serialising the std::expected") { serialiser.serialise(container); }
        }
    }
}

} // namespace morpheus::serialisation
