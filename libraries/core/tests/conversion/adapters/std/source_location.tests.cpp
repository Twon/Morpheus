#include "morpheus/core/conformance/source_location.hpp"
#include "morpheus/core/conversion/adapters/std/source_location.hpp"

#include <catch2/catch_test_macros.hpp>

#include <chrono>
#include <string>
#include <sstream>

namespace morpheus::conversion
{

TEST_CASE("Verify std::format specialisation for std::source_location", "[morpheus.conversion.source_location.formatter]")
{
    auto const currentLocation = MORPHEUS_CURRENT_LOCATION;
    auto const expected =
    [&]
    {
        std::stringstream str;
        str << currentLocation.file_name() << "(" << currentLocation.line() << ":" << currentLocation.column() << "):" << currentLocation.function_name();
        return str.str();
    }();

    REQUIRE(fmt_ns::format("{}", currentLocation) == expected);
}

} // namespace morpheus::conversion
