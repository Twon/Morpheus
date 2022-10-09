#include "core/conformance/format.hpp"
#include "core/serialisation/read_serialiser.hpp"
#include "core/serialisation/serialisers.hpp"

#include <catch2/catch_all.hpp>

using namespace Catch;

namespace morpheus::serialisation
{

namespace {

template<class T>
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
        REQUIRE(deserialise<TestType>(fmt_ns::format("{}", std::numeric_limits<TestType>::min())) == std::numeric_limits<TestType>::min());
        REQUIRE(deserialise<TestType>(fmt_ns::format("{}", std::numeric_limits<TestType>::lowest())) == std::numeric_limits<TestType>::lowest());
        REQUIRE(deserialise<TestType>(fmt_ns::format("{}", std::numeric_limits<TestType>::max())) == std::numeric_limits<TestType>::max());

        if constexpr (not std::is_same_v<TestType, bool>)
            REQUIRE(deserialise<TestType>(fmt_ns::format("{}", std::numeric_limits<TestType>::radix)) == std::numeric_limits<TestType>::radix);
    }
    else if constexpr (std::is_floating_point_v<TestType>)
    {
        REQUIRE(deserialise<TestType>("0") == 0);
        REQUIRE(deserialise<TestType>("-0") == 0);
        REQUIRE(deserialise<TestType>("2.75") == TestType(2.75));
        REQUIRE(deserialise<TestType>("-2.75") == TestType(-2.75));
        REQUIRE(std::isinf(deserialise<TestType>("Infinity")));
        REQUIRE(std::isinf(deserialise<TestType>("-Infinity")));
        REQUIRE(std::isnan(deserialise<TestType>("NaN")));


#if (__cpp_lib_to_chars >= 201611L)
        // RapidJson ouputs "1.401298464324817e-45" vs "1e-45" for float, but SetMaxDecimalPlaces() would effect all non-scientific values so we compare 
        // against the underling value not string representation.
//        REQUIRE(toFloatingPoint<TestType>(serialise(std::numeric_limits<TestType>::denorm_min())) == Approx(std::numeric_limits<TestType>::denorm_min()));
//        REQUIRE(toFloatingPoint<TestType>(serialise(std::numeric_limits<TestType>::denorm_min())) == Approx(std::numeric_limits<TestType>::denorm_min()));
#endif // (__cpp_lib_to_chars >= 201611L)
    }
}

} // namespace morpheus::serialisation