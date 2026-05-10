#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/serialisation/adapters/aggregate.hpp"
#include "morpheus/core/serialisation/adapters/hex.hpp"
#include "morpheus/core/serialisation/adapters/std/array.hpp"
#include "morpheus/core/serialisation/adapters/std/chrono.hpp"
#include "morpheus/core/serialisation/adapters/std/monostate.hpp"
#include "morpheus/core/serialisation/adapters/std/optional.hpp"
#include "morpheus/core/serialisation/adapters/std/pair.hpp"
#include "morpheus/core/serialisation/adapters/std/tuple.hpp"
#include "morpheus/core/serialisation/adapters/std/unique_ptr.hpp"
#include "morpheus/core/serialisation/adapters/std/variant.hpp"
#include "morpheus/core/serialisation/adapters/std/vector.hpp"
#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/json_reader.hpp"
#include "morpheus/core/serialisation/read_serialiser.hpp"
#include "morpheus/core/serialisation/serialisers.hpp"
#include "morpheus/serialisation/types/simple_tuple.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <array>
#include <chrono>
#include <cmath>
#include <compare>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>

using namespace Catch;

namespace morpheus::serialisation
{

namespace test
{

template <typename T>
static T deserialise(std::string_view const value, bool const validate = true)
{
#if (__cpp_lib_sstream_from_string_view >= 202306L)
    std::unique_ptr<std::istream> iss = std::make_unique<std::istringstream>(value);
#else
    std::unique_ptr<std::istream> iss = std::make_unique<std::istringstream>(std::string{value});
#endif
    JsonReadSerialiser serialiser(std::in_place, std::move(iss), validate);
    return serialiser.template deserialise<T>();
}

static JsonReader readerFromString(std::string_view const value)
{
#if (__cpp_lib_sstream_from_string_view >= 202306L)
    std::unique_ptr<std::istream> iss = std::make_unique<std::istringstream>(value);
#else
    std::unique_ptr<std::istream> iss = std::make_unique<std::istringstream>(std::string{value});
#endif
    return JsonReader(std::move(iss), false);
}

} // namespace test

TEST_CASE("Json reader can read string types to underlying text representation", "[morpheus.serialisation.json_reader.special_member_functions]")
{
    STATIC_REQUIRE(std::is_constructible_v<JsonReader, std::unique_ptr<std::istream>, bool>);
    STATIC_REQUIRE_FALSE(std::is_copy_constructible_v<JsonReader>);
    STATIC_REQUIRE_FALSE(std::is_copy_assignable_v<JsonReader>);
    STATIC_REQUIRE_FALSE(std::is_nothrow_copy_constructible_v<JsonReader>);
    STATIC_REQUIRE_FALSE(std::is_nothrow_copy_assignable_v<JsonReader>);
    STATIC_REQUIRE(std::is_move_constructible_v<JsonReader>);
    STATIC_REQUIRE(std::is_move_assignable_v<JsonReader>);
    STATIC_REQUIRE(std::is_nothrow_move_constructible_v<JsonReader>);
    STATIC_REQUIRE(std::is_nothrow_move_assignable_v<JsonReader>);
}

TEMPLATE_TEST_CASE("Json reader can read single native types to underlying text representation",
                   "[morpheus.serialisation.json_reader.native]",
                   bool,
                   std::int8_t,
                   std::uint8_t,
                   std::int16_t,
                   std::uint16_t,
                   std::int32_t,
                   std::uint32_t,
                   std::int64_t,
                   std::uint64_t,
                   float,
                   double)
{
    if constexpr (std::is_integral_v<TestType>)
    {
        using Limits = std::numeric_limits<TestType>;
        REQUIRE(test::deserialise<TestType>(conf::fmt::format("{}", Limits::min())) == Limits::min());
        REQUIRE(test::deserialise<TestType>(conf::fmt::format("{}", Limits::lowest())) == Limits::lowest());
        REQUIRE(test::deserialise<TestType>(conf::fmt::format("{}", Limits::max())) == Limits::max());

        if constexpr (not std::is_same_v<TestType, bool>)
            REQUIRE(test::deserialise<TestType>(conf::fmt::format("{}", Limits::radix)) == Limits::radix);
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

TEST_CASE("Json reader can read string types to underlying text representation", "[morpheus.serialisation.json_reader.string]")
{
    GIVEN("A Json reader")
    {
        WHEN("Reading a string")
        {
            REQUIRE(test::deserialise<std::string>(R"("Hello World")") == "Hello World");
        }
    }
}

// TEST_CASE("Json reader can read sequence types to underlying text representation", "[morpheus.serialisation.json_reader.sequence]")
// {
//     GIVEN("A Json reader")
//     {
//         WHEN("Reading a vector of integers")
//         {
//             auto const value = test::deserialise<std::vector<int>>("[1, 2, 3]");
//             REQUIRE(value == std::vector<int>{1, 2, 3});
//         }
//     }
// }

TEST_CASE("Json reader can read composite types to underlying text representation", "[morpheus.serialisation.json_reader.composite]")
{
    GIVEN("A Json reader")
    {
        WHEN("Reading a composite type")
        {
            auto const value = test::deserialise<std::pair<int, double>>("[1, 2.75]");
            REQUIRE(value == std::pair<int, double>{1, 2.75});
        }
    }
}

// TEST_CASE("Json reader can read complex nested composite types to underlying text representation", "[morpheus.serialisation.json_reader.nested]")
// {
//     GIVEN("A Json reader")
//     {
//         WHEN("Reading a complex nested type")
//         {
//             auto const value = test::deserialise<std::vector<std::pair<int, std::string>>>("[[1, \"one\"], [2, \"two\"]]");
//             REQUIRE(value == std::vector<std::pair<int, std::string>>{
//                                  {1, "one"},
//                                  {2, "two"}
//             });
//         }
//     }
// }

TEST_CASE("Json reader can read nullable types to underlying text representation", "[morpheus.serialisation.json_reader.nullable]")
{
    GIVEN("A Json reader")
    {
        WHEN("Reading an optional value (not null)")
        {
            auto const value = test::deserialise<std::optional<int>>("42");
            REQUIRE(value == std::optional<int>{42});
        }
        WHEN("Reading an optional value (null)")
        {
            auto const value = test::deserialise<std::optional<int>>("null");
            REQUIRE(value == std::optional<int>{std::nullopt});
        }
    }
}

// TEST_CASE("Json reader can read variants to underlying text representation", "[morpheus.serialisation.json_reader.variant]")
// {
//     GIVEN("A Json reader")
//     {
//         WHEN("Reading a variant (first type)")
//         {
//             auto const value = test::deserialise<std::variant<int, std::string>>("42");
//             REQUIRE(std::get<int>(value) == 42);
//         }
//         WHEN("Reading a variant (second type)")
//         {
//             auto const value = test::deserialise<std::variant<int, std::string>>(R"("Hello World")");
//             REQUIRE(std::get<std::string>(value) == "Hello World");
//         }
//     }
//}

TEST_CASE("Json reader can read manual composites", "[morpheus.serialisation.json_reader.manual]")
{
    GIVEN("A Json stream")
    {
        std::string_view str(R"({"key":"value"})");

        WHEN("Read a composite of key pair from the stream")
        {
            JsonReader reader = test::readerFromString(str);

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
            JsonReader reader = test::readerFromString(str);

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

TEST_CASE("Json reader can read single std::byte from underlying text representation", "[morpheus.serialisation.json_reader.byte]")
{
    WHEN("Deserialising a single byte")
    {
        REQUIRE(test::deserialise<std::byte>("42") == std::byte{42});
    }
}

TEST_CASE("Json reader can read byte buffer types from underlying text representation", "[morpheus.serialisation.json_reader.buffers]")
{
    GIVEN("A Json reader")
    {
        WHEN("Reading a Base64 encoded byte buffer into a vector")
        {
            auto const value = test::deserialise<std::vector<std::byte>>(R"("ChQe")");

            THEN("Expect the bytes to be correctly decoded")
            {
                REQUIRE(value.size() == 3);
                REQUIRE(value[0] == std::byte{10});
                REQUIRE(value[1] == std::byte{20});
                REQUIRE(value[2] == std::byte{30});
            }
        }
    }
}

TEST_CASE("Json reader can read std::byte using the Hex adapter", "[morpheus.serialisation.json_reader.hex_adapter]")
{
    GIVEN("A Json stream with a hex string")
    {
        WHEN("Reading using the Hex adapter (0x prefixed)")
        {
            std::byte value{};
            JsonReadSerialiser serialiser(test::readerFromString(R"("0xB4")"));
            deserialise(serialiser, Hex{value});

            THEN("Expect the byte to be correctly parsed")
            {
                REQUIRE(value == std::byte{0xB4});
            }
        }
        WHEN("Reading using the Hex adapter (no prefix)")
        {
            std::byte value{};
            JsonReadSerialiser serialiser(test::readerFromString(R"("A5")"));
            deserialise(serialiser, Hex{value});
            THEN("Expect the byte to be correctly parsed")
            {
                REQUIRE(value == std::byte{0xA5});
            }
        }
    }
}

TEMPLATE_TEST_CASE("Json reader can read multiple integer types using the Hex adapter",
                   "[morpheus.serialisation.json_reader.hex_adapter]",
                   std::uint8_t,
                   std::int8_t,
                   std::uint16_t,
                   std::int16_t,
                   std::uint32_t,
                   std::int32_t,
                   std::uint64_t,
                   std::int64_t)
{
    GIVEN("A Json stream with a hex string")
    {
        WHEN("Reading using the Hex adapter (0x prefixed)")
        {
            TestType value{};
            JsonReadSerialiser serialiser(test::readerFromString(R"("0xFF")"));
            deserialise(serialiser, Hex{value});

            THEN("Expect the value to be correctly parsed")
            {
                REQUIRE(value == TestType{static_cast<TestType>(0xFF)});
            }
        }
        WHEN("Reading using the Hex adapter (no prefix)")
        {
            TestType value{};
            JsonReadSerialiser serialiser(test::readerFromString(R"("FF")"));
            deserialise(serialiser, Hex{value});

            THEN("Expect the value to be correctly parsed")
            {
                REQUIRE(value == TestType{static_cast<TestType>(0xFF)});
            }
        }
    }
}

struct PointComposite
{
    int x;
    double y;

    template <concepts::ReadSerialiser Serialiser>
    void deserialise(Serialiser& s)
    {
        x = s.template deserialise<decltype(x)>("x");
        y = s.template deserialise<decltype(y)>("y");
    }
};

struct NamedPointComposite
{
    PointComposite simple;
    std::string name;

    template <concepts::ReadSerialiser Serialiser>
    void deserialise(Serialiser& s)
    {
        simple = s.template deserialise<decltype(simple)>("simple");
        name = s.template deserialise<decltype(name)>("name");
    }
};

struct BlobComposite
{
    int id = 0;
    std::vector<std::byte> data;
    std::string name;

    template <concepts::ReadSerialiser Serialiser>
    void deserialise(Serialiser& s)
    {
        id = s.template deserialise<decltype(id)>("id");
        data = s.template deserialise<decltype(data)>("data");
        name = s.template deserialise<decltype(name)>("name");
    }
};

TEST_CASE("Json reader can read composite types containing byte buffers", "[morpheus.serialisation.json_reader.composite_buffers]")
{
    GIVEN("A composite type with a byte vector")
    {
        auto const json = R"({"id":1,"data":"ChQe","name":"blob"})";
        auto const composite = test::deserialise<BlobComposite>(json);

        THEN("Expect all fields to be correctly deserialised")
        {
            REQUIRE(composite.id == 1);
            REQUIRE(composite.name == "blob");
            REQUIRE(composite.data.size() == 3);
            REQUIRE(composite.data[0] == std::byte{10});
            REQUIRE(composite.data[1] == std::byte{20});
            REQUIRE(composite.data[2] == std::byte{30});
        }
    }
}

// TEST_CASE("Json reader can read nested composites in arrays", "[morpheus.serialisation.json_reader.nested_composites]")
// {
//     GIVEN("An array of composites")
//     {
//         auto const json = R"([{"x":1,"y":1.5}, {"x":2,"y":2.5}])";
//         auto const value = test::deserialise<std::vector<PointComposite>>(json);

//         THEN("Expect both composites to be correctly deserialised")
//         {
//             REQUIRE(value.size() == 2);
//             REQUIRE(value[0].x == 1);
//             REQUIRE(value[0].y == 1.5);
//             REQUIRE(value[1].x == 2);
//             REQUIRE(value[1].y == 2.5);
//         }
//     }
// }

struct SimpleComposite
{
    int first = 0;
    bool second = false;
    float third = 0.0f;
    std::string forth;

    template <concepts::ReadSerialiser Serialiser>
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

    template <concepts::ReadSerialiser Serialiser>
    void deserialise(Serialiser& s)
    {
        first = s.template deserialise<decltype(first)>("first");
        second = s.template deserialise<decltype(second)>("second");
    }
};

TEST_CASE("Json reader can read simple composite types from underlying test representation", "[morpheus.serialisation.json_reader.composite.legacy]")
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

TEST_CASE("Json reader handles missing fields gracefully", "[morpheus.serialisation.json_reader.error_handling]")
{
    GIVEN("A test type for validating serialition of specific types")
    {
        using IntegralType = ContainsType<std::int32_t>;
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

TEST_CASE("Json reader throws an error on invalid json input", "[morpheus.serialisation.json_reader.invalid_json]")
{
    GIVEN("A type serialising a integer")
    {
        using IntegralType = ContainsType<std::int32_t>;
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
    SECTION("Chrono types")
    {
        REQUIRE(test::deserialise<std::chrono::nanoseconds>(R"("123ns")") == std::chrono::nanoseconds{123});
        REQUIRE(test::deserialise<std::chrono::microseconds>(R"("456us")") == std::chrono::microseconds{456});
        REQUIRE(test::deserialise<std::chrono::milliseconds>(R"("789ms")") == std::chrono::milliseconds{789});
        REQUIRE(test::deserialise<std::chrono::seconds>(R"("123s")") == std::chrono::seconds{123});
        REQUIRE(test::deserialise<std::chrono::minutes>(R"("58min")") == std::chrono::minutes{58});
        REQUIRE(test::deserialise<std::chrono::hours>(R"("24h")") == std::chrono::hours{24});
        REQUIRE(test::deserialise<std::chrono::days>(R"("8d")") == std::chrono::days{8});
        REQUIRE(test::deserialise<std::chrono::weeks>(R"("12w")") == std::chrono::weeks{12});
        REQUIRE(test::deserialise<std::chrono::years>(R"("100y")") == std::chrono::years{100});
        REQUIRE(test::deserialise<std::chrono::months>(R"("12m")") == std::chrono::months{12});
    }
    REQUIRE(test::deserialise<std::monostate>(R"({})") == std::monostate{});
    REQUIRE(test::deserialise<std::optional<int>>(R"(100)") == std::optional<int>{100});
    REQUIRE(test::deserialise<std::optional<int>>(R"(null)") == std::optional<int>{});
    REQUIRE(test::deserialise<std::pair<int, bool>>(R"([50,true])") == std::pair<int, bool>{50, true});
    REQUIRE(test::deserialise<std::string>(R"("Hello")") == std::string("Hello"));
    REQUIRE(test::deserialise<std::tuple<int, bool, std::string>>(R"([75,true,"Example"])") == std::tuple<int, bool, std::string>{75, true, "Example"});
    //    REQUIRE(test::deserialise<std::variant<int, bool, std::string>>(R"({"type":"bool","value":true})") == std::variant<int, bool, std::string>{true});
    REQUIRE(test::deserialise<std::vector<int>>(R"([1, 2, 3, 4, 5])") == std::vector<int>{1, 2, 3, 4, 5});
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

TEST_CASE("Json reader can read ranges of composites", "[morpheus.serialisation.range.deserialise.composites]")
{
    // auto const value = std::vector<testing::SimpleTuple>{
    //     {1, true,       {std::byte{1}, std::byte{2}, std::byte{3}}},
    //     {2, true,    {std::byte{10}, std::byte{20}, std::byte{30}}},
    //     {3, true, {std::byte{100}, std::byte{200}, std::byte{255}}}
    // };
    // REQUIRE(conf::fmt::format("{}", value) ==
    //         R"([{first=1,second=true,data=[1, 2, 3]}, {first=2,second=true,data=[10, 20, 30]}, {first=3,second=true,data=[100, 200, 255]}])");

    REQUIRE(test::deserialise<std::vector<testing::SimpleTuple>>(
                R"([{"first":1,"second":true,"data":"AQID"},{"first":2,"second":true,"data":"ChQe"},{"first":3,"second":true,"data":"ZMj/"}])") ==
            std::vector<testing::SimpleTuple>{
                {1, true,       {std::byte{1}, std::byte{2}, std::byte{3}}},
                {2, true,    {std::byte{10}, std::byte{20}, std::byte{30}}},
                {3, true, {std::byte{100}, std::byte{200}, std::byte{255}}}
    });
    using Catch::Matchers::ContainsSubstring;
    REQUIRE_THROWS_WITH(
        test::deserialise<std::vector<testing::SimpleTuple>>(
            R"([{"first":1,"second":true,"data":"AQID"},{"first":2,"second":true,"data":"ChQe"},{"first":3,"second":true,"data":"ZMj/"})", false),
        ContainsSubstring("Parse error at offset"));
}

} // namespace morpheus::serialisation
