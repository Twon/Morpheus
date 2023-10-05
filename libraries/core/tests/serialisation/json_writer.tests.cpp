#include "morpheus/core/serialisation/json_writer.hpp"
#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/serialisation/adapters/aggregate.hpp"
#include "morpheus/core/serialisation/adapters/std/chrono.hpp"
#include "morpheus/core/serialisation/adapters/std/monostate.hpp"
#include "morpheus/core/serialisation/adapters/std/optional.hpp"
#include "morpheus/core/serialisation/adapters/std/pair.hpp"
#include "morpheus/core/serialisation/adapters/std/ranges.hpp"
#include "morpheus/core/serialisation/adapters/std/tuple.hpp"
#include "morpheus/core/serialisation/adapters/std/unique_ptr.hpp"
#include "morpheus/core/serialisation/adapters/std/variant.hpp"
#include "morpheus/core/serialisation/adapters/std/vector.hpp"
#include "morpheus/core/serialisation/serialisers.hpp"
#include "morpheus/core/serialisation/write_serialiser.hpp"

#include <catch2/catch_all.hpp>
#include <charconv>
#include <limits>
#include <string>
#include <system_error>

using namespace Catch;

namespace morpheus::serialisation
{

namespace test {

template<class T>
std::string serialise(T const& value)
{
    std::ostringstream oss;
    JsonWriteSerialiser serialiser{oss};
    serialiser.serialise<T>(value);
    return oss.str();
}

#if (__cpp_lib_to_chars >= 201611L)
template<typename T> requires std::is_floating_point_v<T>
T toFloatingPoint(std::string_view value)
{
    T result = 0;
    auto [ptr, ec] { std::from_chars(value.data(), value.data() + value.size(), result) };

    if (ec != std::errc())
    {
        throw std::system_error(std::make_error_code(ec));
    }
    return result;
}
#endif // (__cpp_lib_to_chars >= 201611L)

}

TEMPLATE_TEST_CASE("Json writer can write single native types to underlying text representation", "[morpheus.serialisation.json_writer.native]", 
    bool, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t, float, double)
{
    if constexpr (std::is_integral_v<TestType>)
    {
        REQUIRE(test::serialise(std::numeric_limits<TestType>::min()) == fmt_ns::format("{}", std::numeric_limits<TestType>::min()));
        REQUIRE(test::serialise(std::numeric_limits<TestType>::lowest()) == fmt_ns::format("{}", std::numeric_limits<TestType>::lowest()));
        REQUIRE(test::serialise(std::numeric_limits<TestType>::max()) == fmt_ns::format("{}", std::numeric_limits<TestType>::max()));
        REQUIRE(test::serialise(std::numeric_limits<TestType>::radix) == fmt_ns::format("{}", std::numeric_limits<TestType>::radix));
    }
    else if constexpr (std::is_floating_point_v<TestType>)
    {
        REQUIRE(test::serialise(0) == "0");
        REQUIRE(test::serialise(-0) == "0");
        REQUIRE(test::serialise(TestType(2.75)) == "2.75");
        REQUIRE(test::serialise(TestType(-2.75)) == "-2.75");
        REQUIRE(test::serialise(std::numeric_limits<TestType>::infinity()) == "Infinity");
        REQUIRE(test::serialise(-std::numeric_limits<TestType>::infinity()) == "-Infinity");
        REQUIRE(test::serialise(std::numeric_limits<TestType>::quiet_NaN()) == "NaN");
        REQUIRE(test::serialise(-std::numeric_limits<TestType>::quiet_NaN()) == "NaN");
        REQUIRE(test::serialise(std::numeric_limits<TestType>::signaling_NaN()) == "NaN");
        REQUIRE(test::serialise(-std::numeric_limits<TestType>::signaling_NaN()) == "NaN");

#if (__cpp_lib_to_chars >= 201611L)
        // RapidJson ouputs "1.401298464324817e-45" vs "1e-45" for float, but SetMaxDecimalPlaces() would effect all non-scientific values so we compare 
        // against the underling value not string representation.
//        REQUIRE(test::toFloatingPoint<TestType>(test::serialise(std::numeric_limits<TestType>::denorm_min())) == Approx(std::numeric_limits<TestType>::denorm_min()));
//        REQUIRE(test::toFloatingPoint<TestType>(test::serialise(std::numeric_limits<TestType>::denorm_min())) == Approx(std::numeric_limits<TestType>::denorm_min()));
#endif // (__cpp_lib_to_chars >= 201611L)
    }        
}

TEST_CASE("Json writer can write simple composite types to underlying text representation", "[morpheus.serialisation.json_writer.composite]")
{
    GIVEN("A Json writer")
    {
        std::ostringstream strStream;
        JsonWriter writer{ strStream };

        WHEN("Writing an empty composite")
        {
            writer.beginComposite();
            writer.endComposite();

            THEN("Expect an empty composite in the json document")
            {
                REQUIRE(strStream.str() == "{}");
            }
        }
        WHEN("Writing an empty composite")
        {
            writer.beginComposite();
            writer.beginValue("x");
            writer.beginNullable(true);
            writer.endNullable();
            writer.endValue();
            writer.endComposite();

            THEN("Expect an null composite in the json document")
            {
                REQUIRE(strStream.str() == R"({"x":null})");
            }
        }
        WHEN("Writing an simple composite with single value")
        {
            writer.beginComposite();
            writer.beginValue("key");
            writer.write("value");
            writer.endValue();
            writer.endComposite();

            THEN("Expect an empty composite in the json document")
            {
                REQUIRE(strStream.str() == R"({"key":"value"})");
            }
        }
        WHEN("Writing an simple composite with multiple values")
        {
            writer.beginComposite();
            writer.beginValue("1");
            writer.write("A");
            writer.endValue();
            writer.beginValue("2");
            writer.write("B");
            writer.endValue();
            writer.beginValue("3");
            writer.write("C");
            writer.endValue();
            writer.endComposite();

            THEN("Expect an empty composite in the json document")
            {
                REQUIRE(strStream.str() == R"({"1":"A","2":"B","3":"C"})");
            }
        }
    }
}

TEST_CASE("Json writer can write simple sequence types to underlying text representation", "[morpheus.serialisation.json_writer.squence]")
{
    GIVEN("A Json writer")
    {
        std::ostringstream strStream;
        JsonWriter writer{ strStream };

        WHEN("Writing an simple value")
        {
            writer.write("value");

            THEN("Expect an empty composite in the json document")
            {
                REQUIRE(strStream.str() == R"("value")");
            }
        }
        WHEN("Writing an empty sequence")
        {
            writer.beginSequence();
            writer.endSequence();

            THEN("Expect an empty composite in the json document")
            {
                REQUIRE(strStream.str() == "[]");
            }
        }
        WHEN("Writing an simple composite with single value")
        {
            writer.beginSequence();
            writer.write("value");
            writer.endSequence();

            THEN("Expect an empty composite in the json document")
            {
                REQUIRE(strStream.str() == R"(["value"])");
            }
        }
        WHEN("Writing an simple composite with multiple values")
        {
            writer.beginSequence();
            writer.write("A");
            writer.write("B");
            writer.write("C");
            writer.endSequence();

            THEN("Expect an empty composite in the json document")
            {
                REQUIRE(strStream.str() == R"(["A","B","C"])");
            }
        }
    }
}

struct Example
{
    int a = 0;
    bool b = true;
    std::string c = "Example";
};

template<>
inline constexpr bool delegateAggregateSerialisation<Example> = true;

struct Example2
{
    int a = 0;
    Example b;
    bool c = true;
};

template<>
inline constexpr bool delegateAggregateSerialisation<Example2> = true;

TEST_CASE("Json writer can write simple aggregates types to underlying text representation", "[morpheus.serialisation.json_writer.aggregate]")
{
    GIVEN("An aggregate that opts into serialisation")
    {
        STATIC_REQUIRE(SerialisableAggregate<Example>);

        WHEN("Writing default intialised instance")
        {
            THEN("Expect the aggregate values serialised as a sequence")
            {
                REQUIRE(test::serialise(Example{}) == R"([0,true,"Example"])");
            }
        }
    }
    GIVEN("An aggregate containing aggregates that all opt into serialisation")
    {
        STATIC_REQUIRE(SerialisableAggregate<Example2>);

        WHEN("Writing default intialised instance")
        {
            THEN("Expect the aggregate values serialised as a sequence embedding in a sequence")
            {
                REQUIRE(test::serialise(Example2{}) == R"([0,[0,true,"Example"],true])");
            }
        }
    }
}

TEST_CASE("Json writer can write std types to underlying text representation", "[morpheus.serialisation.json_writer.adapters.std]")
{
    SECTION("Chrono types")
    {
       REQUIRE(test::serialise(std::chrono::nanoseconds{123}) == R"("123ns")");
       REQUIRE(test::serialise(std::chrono::microseconds{456}) == R"("456us")");
       REQUIRE(test::serialise(std::chrono::milliseconds{789}) == R"("789ms")");
       REQUIRE(test::serialise(std::chrono::seconds{123}) == R"("123s")");
       REQUIRE(test::serialise(std::chrono::minutes{58}) == R"("58min")");
       REQUIRE(test::serialise(std::chrono::hours{24}) == R"("24h")");
       REQUIRE(test::serialise(std::chrono::days{8}) == R"("8d")");
       REQUIRE(test::serialise(std::chrono::weeks{12}) == R"("12w")");
       REQUIRE(test::serialise(std::chrono::years{100}) == R"("100y")");
       REQUIRE(test::serialise(std::chrono::months{12}) == R"("12m")");
    }
    REQUIRE(test::serialise(std::monostate{}) == R"({})");
    REQUIRE(test::serialise(std::optional<int>{100}) == R"(100)");
    REQUIRE(test::serialise(std::optional<int>{}) == R"(null)");
    REQUIRE(test::serialise(std::pair<int, bool>{50, true}) == R"([50,true])");
    REQUIRE(test::serialise(std::string("Hello")) == R"("Hello")");
    REQUIRE(test::serialise(std::tuple<int, bool, std::string>{75, true, "Example"}) == R"([75,true,"Example"])");
    REQUIRE(test::serialise(std::make_unique<int>(123)) == R"(123)");
    REQUIRE(test::serialise(std::variant<int, bool, std::string>{true}) == R"({"type":"bool","value":true})");
    REQUIRE(test::serialise(std::vector<int>{0,1,2,3,4,5}) == R"([0,1,2,3,4,5])");
    static_assert(ranges::range<std::vector<int>>);
}

} // namespace morpheus::serialisation