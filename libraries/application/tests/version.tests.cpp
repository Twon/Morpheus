#include <morpheus/application/version.hpp>
#include <morpheus/core/conformance/format.hpp>
#include <morpheus/core/conformance/scan.hpp>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

namespace morpheus::application
{

TEST_CASE("Ensure format is supported for versions", "[morpheus.application.version.fmt]")
{
    Version latest{.major = 1, .minor = 0, .patch = 99};
    REQUIRE(fmt_ns::format("{}", latest) == "{major=1,minor=0,patch=99}");
}

TEST_CASE("Ensure scan is supported and working for custom versions", "[morpheus.application.version.scan]")
{
    GIVEN("A custom format string representing a version")
    {
        using namespace std::string_view_literals;
        auto const input = "{major=1,minor=0,patch=99}"sv;

        WHEN("Using std::scan to the coordinate via a customisation point")
        {
            auto result = scan_ns::scan<Version>(input, "{}");

            REQUIRE(result);
            auto [version] = result->values();

            THEN("Expect the variables wrote to the stream in the specified order")
            {
                REQUIRE(version.major == 1);
                REQUIRE(version.minor == 0);
                REQUIRE(version.patch == 99);
            }
        }
    }
}

} // namespace morpheus::application
