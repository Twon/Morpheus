#include "core/conformance/format.hpp"
#include "core/serialisation/json_writer.hpp"
#include "core/serialisation/serialisers.hpp"
#include "core/serialisation/write_serialiser.hpp"

#include <catch2/catch_all.hpp>
#include <charconv>
#include <limits>
#include <string>
#include <system_error>

using namespace Catch;

namespace morpheus::serialisation
{

namespace {

template<class T>
std::string serialise(T const& value)
{
    std::ostringstream oss;
    JsonWriteSerialiser serialiser{oss};
    serialiser.serialise(value);
    return oss.str();
}

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

}

TEMPLATE_TEST_CASE("Json writer can write single native types to underlying text representation", "[morpheus.serialisation.json_writer.native]", 
    bool, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t, float, double)
{
    if constexpr (std::is_integral_v<TestType>)
    {
        REQUIRE(serialise(std::numeric_limits<TestType>::min()) == fmt_ns::format("{}", std::numeric_limits<TestType>::min()));
        REQUIRE(serialise(std::numeric_limits<TestType>::lowest()) == fmt_ns::format("{}", std::numeric_limits<TestType>::lowest()));
        REQUIRE(serialise(std::numeric_limits<TestType>::max()) == fmt_ns::format("{}", std::numeric_limits<TestType>::max()));
        REQUIRE(serialise(std::numeric_limits<TestType>::radix) == fmt_ns::format("{}", std::numeric_limits<TestType>::radix));
    }
    else if constexpr (std::is_floating_point_v<TestType>)
    {
        REQUIRE(serialise(0) == "0");
        REQUIRE(serialise(-0) == "0");
        REQUIRE(serialise(TestType(2.75)) == "2.75");
        REQUIRE(serialise(TestType(-2.75)) == "-2.75");
        REQUIRE(serialise(std::numeric_limits<TestType>::infinity()) == "Infinity");
        REQUIRE(serialise(-std::numeric_limits<TestType>::infinity()) == "-Infinity");
        REQUIRE(serialise(std::numeric_limits<TestType>::quiet_NaN()) == "NaN");
        REQUIRE(serialise(-std::numeric_limits<TestType>::quiet_NaN()) == "NaN");
        REQUIRE(serialise(std::numeric_limits<TestType>::signaling_NaN()) == "NaN");
        REQUIRE(serialise(-std::numeric_limits<TestType>::signaling_NaN()) == "NaN");

        // RapidJson ouputs "1.401298464324817e-45" vs "1e-45" for float, but SetMaxDecimalPlaces() would effect all non-scientific values so we compare 
        // against the underling value not string representation.
        REQUIRE(toFloatingPoint<TestType>(serialise(std::numeric_limits<TestType>::denorm_min())) == Approx(std::numeric_limits<TestType>::denorm_min()));
        REQUIRE(toFloatingPoint<TestType>(serialise(std::numeric_limits<TestType>::denorm_min())) == Approx(std::numeric_limits<TestType>::denorm_min()));
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

} // namespace morpheus::serialisation