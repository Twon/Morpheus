#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/serialisation/adapters/aggregate.hpp"
#include "morpheus/core/serialisation/adapters/std/optional.hpp"
#include "morpheus/core/serialisation/adapters/std/pair.hpp"
#include "morpheus/core/serialisation/adapters/std/tuple.hpp"
#include "morpheus/core/serialisation/adapters/std/unique_ptr.hpp"
#include "morpheus/core/serialisation/adapters/std/variant.hpp"
#include "morpheus/core/serialisation/read_serialiser.hpp"
#include "morpheus/core/serialisation/serialisers.hpp"

#include <catch2/catch_all.hpp>

using namespace Catch;

namespace morpheus::serialisation
{

namespace test {

template<typename T>
T deserialise(std::string_view const value)
{
    std::istringstream iss(std::string{value});
    JsonReaderSerialiser serialiser{iss};
    return serialiser.deserialise<T>();
}

}

TEMPLATE_TEST_CASE("Json writer can write single native types to underlying text representation", "[morpheus.serialisation.json_reader.native]", 
    bool, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t, float, double)
{
    if constexpr (std::is_integral_v<TestType>)
    {
        REQUIRE(test::deserialise<TestType>(fmt_ns::format("{}", std::numeric_limits<TestType>::min())) == std::numeric_limits<TestType>::min());
        REQUIRE(test::deserialise<TestType>(fmt_ns::format("{}", std::numeric_limits<TestType>::lowest())) == std::numeric_limits<TestType>::lowest());
        REQUIRE(test::deserialise<TestType>(fmt_ns::format("{}", std::numeric_limits<TestType>::max())) == std::numeric_limits<TestType>::max());

        if constexpr (not std::is_same_v<TestType, bool>)
            REQUIRE(test::deserialise<TestType>(fmt_ns::format("{}", std::numeric_limits<TestType>::radix)) == std::numeric_limits<TestType>::radix);
    }
    else if constexpr (std::is_floating_point_v<TestType>)
    {
        REQUIRE(test::deserialise<TestType>("0") == 0);
        REQUIRE(test::deserialise<TestType>("-0") == 0);
        REQUIRE(test::deserialise<TestType>("2.75") == TestType(2.75));
        REQUIRE(test::deserialise<TestType>("-2.75") == TestType(-2.75));
        REQUIRE(std::isinf(test::deserialise<TestType>("Infinity")));
        REQUIRE(std::isinf(test::deserialise<TestType>("-Infinity")));
        REQUIRE(std::isnan(test::deserialise<TestType>("NaN")));
    }
}

TEST_CASE("Json reader providess basic reader functionality", "[morpheus.serialisation.json_reader.fundamental]")
{
    GIVEN("A Json stream")
    {
        std::istringstream iss(R"("value")");

        WHEN("Read an single value from the stream")
        {
            JsonReader reader{ iss };

            THEN("Expect an empty composite in the json document")
            {
                REQUIRE("value" == reader.read<std::string>());
            }
        }
    }
    GIVEN("A Json stream")
    {
        std::istringstream iss(R"({})");

        WHEN("Read an empty composite from the stream")
        {
            JsonReader reader{ iss };

            THEN("Expect an empty composite in the json document")
            {
                reader.beginComposite();
                reader.endComposite();
            }
        }
    }
    GIVEN("A Json stream")
    {
        std::istringstream iss(R"({"key":"value"})");

        WHEN("Read a composite of key pair from the stream")
        {
            JsonReader reader{ iss };

            THEN("Expect an empty composite in the json document")
            {
                reader.beginComposite();
                reader.beginValue("key");
                REQUIRE("value" == reader.read<std::string>());
                reader.endValue();
                reader.endComposite();
            }
        }
    }
    GIVEN("A Json stream")
    {
        std::istringstream iss(R"({"x":null})");

        WHEN("Read a composite of key to null pair from the stream")
        {
            JsonReader reader{ iss };
            THEN("Expect an empty composite in the json document")
            {
                reader.beginComposite();
                reader.beginValue("x");
                REQUIRE(true == reader.beginNullable());
                reader.endNullable();
                reader.endValue();
                reader.endComposite();
            }
        }
    }
}

struct SimpleComposite
{
    int first = 0;
    bool second = false;
    float third = 0.0f;
    std::string forth;

    template<concepts::ReadSerialiser Serialiser>
    void deserialise(Serialiser& s)
    {
        first = s.template deserialise<decltype(first)>("first");
        second = s.template deserialise<decltype(second)>("second");
        third = s.template deserialise<decltype(third)>("third");
        forth = s.template deserialise<decltype(forth)>("forth");
    }
};

struct ComplexComposite
{
    SimpleComposite first;
    float second = 0.0f;

    template<concepts::ReadSerialiser Serialiser>
    void deserialise(Serialiser& s)
    {
        first = s.template deserialise<decltype(first)>("first");
        second = s.template deserialise<decltype(second)>("second");
    }
};

TEST_CASE("Json reader can read simple composite types from underlying test representation", "[morpheus.serialisation.json_reader.composite]")
{
    GIVEN("A Json reader")
    {
        auto const simple = test::deserialise<SimpleComposite>(R"({"first":100,"second":true,"third":50,"forth":"example"})");
        STATIC_REQUIRE(concepts::ReadSerialisableInsrusive<SimpleComposite>);
        
        WHEN("Writing an empty composite")
        {
            THEN("Expect an empty composite in the json document")
            {
                REQUIRE(simple.first == 100);
                REQUIRE(simple.second == true);
                REQUIRE(simple.third == 50.0);
                REQUIRE(simple.forth == "example");
            }
        }
    }
    GIVEN("A Json reader")
    {
        auto const complex = test::deserialise<ComplexComposite>(R"({"first":{"first":100,"second":true,"third":50,"forth":"example"},"second":3.14})");
        STATIC_REQUIRE(concepts::ReadSerialisableInsrusive<ComplexComposite>);

        WHEN("Writing an empty composite")
        {
            THEN("Expect an empty composite in the json document")
            {
                REQUIRE(complex.first.first == 100);
                REQUIRE(complex.first.second == true);
                REQUIRE(complex.first.third == 50.0);
                REQUIRE(complex.first.forth == "example");
                REQUIRE(complex.second == Approx(3.14));
            }
        }
    }
}

TEST_CASE("Json reader can read std types from underlying text representation", "[morpheus.serialisation.json_reader.adapters.std]")
{
    REQUIRE(test::deserialise<std::pair<int, bool>>(R"([50,true])") == std::pair<int, bool>{50, true});
    REQUIRE(test::deserialise<std::tuple<int, bool, std::string>>(R"([75,true,"Example"])") == std::tuple<int, bool, std::string>{75, true, "Example"});
//    REQUIRE(test::deserialise<std::variant<int, bool, std::string>>(R"({"type":"bool","value":true})") == std::variant<int, bool, std::string>{true});
//    REQUIRE(test::deserialise<std::unique_ptr<int>>(R"({50})") == std::make_unique<int>(50));
}

} // namespace morpheus::serialisation