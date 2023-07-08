#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/serialisation/adapters/aggregate.hpp"
#include "morpheus/core/serialisation/adapters/std/optional.hpp"
#include "morpheus/core/serialisation/adapters/std/pair.hpp"
#include "morpheus/core/serialisation/adapters/std/tuple.hpp"
#include "morpheus/core/serialisation/adapters/std/unique_ptr.hpp"
#include "morpheus/core/serialisation/adapters/std/variant.hpp"
#include "morpheus/core/serialisation/adapters/std/vector.hpp"
#include "morpheus/core/serialisation/read_serialiser.hpp"
#include "morpheus/core/serialisation/serialisers.hpp"

#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

using namespace Catch;

namespace morpheus::serialisation
{

namespace test {

struct ISteamCopier
{
    using deleter_type = std::default_delete<std::istream>;

    std::istream* operator()(std::istream const& rhs) const
    {
        auto ss = std::make_unique<std::istream>(rhs.rdbuf());
        return ss.release();
    }

    std::istringstream* operator()(std::istringstream const& rhs) const
    {
        auto ss = std::make_unique<std::istringstream>(rhs.str());
        return ss.release();
    }
};

template<typename T>
T deserialise(std::string_view const value, bool const validate = true)
{
    using namespace memory;
    auto strstream = std::make_unique<std::istringstream>(std::string{value});
    auto iss = polymorphic_value<std::istream>(strstream.release(), ISteamCopier{});
    JsonReaderSerialiser serialiser(std::move(iss), validate);
    return serialiser.deserialise<T>();
}

auto readerFromString(std::string_view const value)
{
    using namespace memory;
    auto strstream = std::make_unique<std::istringstream>(std::string{value});
    auto iss = polymorphic_value<std::istream>(strstream.release(), ISteamCopier{});
    return JsonReader(std::move(iss), false);
}

} // namespace test

TEMPLATE_TEST_CASE("Json writer can write single native types to underlying text representation", "[morpheus.serialisation.json_reader.native]", 
    bool, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t, float, double)
{
    if constexpr (std::is_integral_v<TestType>)
    {
        using Limits = std::numeric_limits<TestType>;
        REQUIRE(test::deserialise<TestType>(fmt_ns::format("{}", Limits::min())) == Limits::min());
        REQUIRE(test::deserialise<TestType>(fmt_ns::format("{}", Limits::lowest())) == Limits::lowest());
        REQUIRE(test::deserialise<TestType>(fmt_ns::format("{}", Limits::max())) == Limits::max());

        if constexpr (not std::is_same_v<TestType, bool>)
            REQUIRE(test::deserialise<TestType>(fmt_ns::format("{}", Limits::radix)) == Limits::radix);
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

TEST_CASE("Create and then copy a reader and read from the copied stream", "[morpheus.serialisation.json_reader.copy")
{
    GIVEN("A Json stream")
    {
        std::string_view str(R"("value")");

        WHEN("Read an single value from the stream")
        {
            JsonReader reader = test::readerFromString(str);
            JsonReader copiedReader(reader);

            THEN("Expect an empty composite in the json document") { REQUIRE("value" == copiedReader.read<std::string>()); }
        }
    }
}

TEST_CASE("Json reader providess basic reader functionality", "[morpheus.serialisation.json_reader.fundamental]")
{
    GIVEN("A Json stream")
    {
        std::string_view str(R"("value")");

        WHEN("Read an single value from the stream")
        {
            JsonReader reader =  test::readerFromString(str);

            THEN("Expect an empty composite in the json document")
            {
                REQUIRE("value" == reader.read<std::string>());
            }
        }
    }
    GIVEN("A Json stream")
    {
        std::string_view str(R"({})");

        WHEN("Read an empty composite from the stream")
        {
            JsonReader reader =  test::readerFromString(str);

            THEN("Expect an empty composite in the json document")
            {
                reader.beginComposite();
                reader.endComposite();
            }
        }
    }
    GIVEN("A Json stream")
    {
        std::string_view str(R"({"key":"value"})");

        WHEN("Read a composite of key pair from the stream")
        {
            JsonReader reader =  test::readerFromString(str);

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
        std::string_view str(R"({"x":null})");

        WHEN("Read a composite of key to null pair from the stream")
        {
            JsonReader reader =  test::readerFromString(str);

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

template <typename T>
struct ContainsType
{
    T value = T();

    template <concepts::ReadSerialiser Serialiser>
    void deserialise(Serialiser& s)
    {
        value = s.template deserialise<decltype(value)>("value");
    }
};

TEST_CASE("Json reader raise an error on reading incorrect types", "[morpheus.serialisation.json_reader.invalid_values]")
{
    GIVEN("A test type for validating serialition of specific types")
    {
        using IntegralType = ContainsType<std::int32_t>;
        IntegralType value;
        WHEN("Deserialising from Json with a string where a integer is expected")
        {
            auto const jsonText = R"({"value":100})";
            THEN("Ensure serialisation works with valid input")
            {
                using Catch::Matchers::ContainsSubstring;
                REQUIRE(test::deserialise<IntegralType>(jsonText, false).value == 100);
            }
        }
    }
    GIVEN("A type serialising a integer")
    {
        using IntegralType = ContainsType<std::int32_t>;
        IntegralType value;
        WHEN("Deserialising from Json with a string where a integer is expected")
        {
            auto const jsonText = R"({"value":"InvalidValue"})";
            THEN("Expect an exception to be thrown on error to convert a string to a integer")
            {
                using Catch::Matchers::ContainsSubstring;
                REQUIRE_THROWS_WITH(test::deserialise<IntegralType>(jsonText, false), ContainsSubstring("Unable to convert to integral"));
            }
        }
    }
    GIVEN("A type serialising a float")
    {
        using FloatType = ContainsType<float>;
        FloatType value;
        WHEN("Deserialising from Json with a string where a float is expected")
        {
            auto const jsonText = R"({"value":"InvalidValue"})";
            THEN("Expect an exception to be thrown on error to convert a string to a float")
            {
                using Catch::Matchers::ContainsSubstring;
                REQUIRE_THROWS_WITH(test::deserialise<FloatType>(jsonText, false), ContainsSubstring("Unable to convert to floating point"));
            }
        }
    }
}

TEST_CASE("Json reader thows an error on invalid json input", "[morpheus.serialisation.json_reader.invalid_json]")
{
    GIVEN("A type serialising a integer")
    {
        using IntegralType = ContainsType<std::int32_t>;
        IntegralType value;
        WHEN("Deserialising from invalid Json")
        {
            auto const jsonText = R"({"value" @ "AtSymbolIsNotAValidSeperator"})";
            THEN("Expect an exception to be thrown on error to convert a string to a integer")
            {
                using Catch::Matchers::ContainsSubstring;
                REQUIRE_THROWS_WITH(test::deserialise<IntegralType>(jsonText, false), ContainsSubstring("Parse error at offset"));
            }
        }
    }
}

TEST_CASE("Json reader can read std types from underlying text representation", "[morpheus.serialisation.json_reader.adapters.std]")
{
    REQUIRE(test::deserialise<std::optional<int>>(R"(100)") == std::optional<int>{100});
    REQUIRE(test::deserialise<std::optional<int>>(R"(null)") == std::optional<int>{});
    REQUIRE(test::deserialise<std::pair<int, bool>>(R"([50,true])") == std::pair<int, bool>{50, true});
    REQUIRE(test::deserialise<std::tuple<int, bool, std::string>>(R"([75,true,"Example"])") == std::tuple<int, bool, std::string>{75, true, "Example"});
//    REQUIRE(test::deserialise<std::variant<int, bool, std::string>>(R"({"type":"bool","value":true})") == std::variant<int, bool, std::string>{true});
    REQUIRE(*test::deserialise<std::unique_ptr<int>>(R"(50)") == 50);
}

TEST_CASE("Error handling test cases for unexpected errors in the input Json stream", "[morpheus.serialisation.json_reader.error_handling]")
{
    using Catch::Matchers::ContainsSubstring;
    REQUIRE_THROWS_WITH(test::readerFromString("50").beginValue("expected_key"),
                        ContainsSubstring("BeginComposite expected") && ContainsSubstring("Value encountered"));
    REQUIRE_THROWS_WITH(test::readerFromString("[1,2,3]").beginValue("expected_key"),
                        ContainsSubstring("BeginComposite expected") && ContainsSubstring("BeginSequence encountered"));
    REQUIRE_THROWS_WITH(test::readerFromString("{}").beginValue("expected_key"), ContainsSubstring("empty composite"));

    GIVEN("A type which parses a key value pair")
    {
        using IntegralType = ContainsType<std::int32_t>;
        IntegralType value;
        WHEN("Deserialising from Json with an invalid type for the key (i.e. an integer not a string)")
        {
            auto const jsonText = R"({100:100})";
            THEN("Ensure serialisation captures the error in key type")
            {
                using Catch::Matchers::ContainsSubstring;
                REQUIRE_THROWS_WITH(test::deserialise<IntegralType>(jsonText, false), ContainsSubstring("error kParseErrorObjectMissName"));
            }
        }
    }
    GIVEN("A type which parses a key value pair")
    {
        using IntegralType = ContainsType<std::int32_t>;
        IntegralType value;
        WHEN("Deserialising from Json with an invalid key")
        {
            auto const jsonText = R"({"incorrect_key":100})";
            THEN("Ensure serialisation captures the error in key type")
            {
                using Catch::Matchers::ContainsSubstring;
                REQUIRE_THROWS_WITH(test::deserialise<IntegralType>(jsonText, false),
                                    ContainsSubstring("Expected key value") && ContainsSubstring("actual key incorrect_key"));
            }
        }
    }
}

} // namespace morpheus::serialisation