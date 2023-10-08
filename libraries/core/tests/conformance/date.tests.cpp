#include "morpheus/core/conformance/date.hpp"

#include <catch2/catch_all.hpp>

namespace morpheus
{

TEST_CASE("Ensure date library is supported and working", "[morpheus.conformance.date]")
{
    using namespace std::chrono_literals;
    using namespace date_ns;

    // Ensure time zones work
    REQUIRE(date_ns::locate_zone("Europe/London"));

    STATIC_REQUIRE((year{ 2022 } / month{ 11 } / day{ 8 }) == year_month_day(year{ 2022 }, month{ 11 }, day{ 8 }));
    STATIC_REQUIRE(weeks{ 1 } == days{ 7 });
    STATIC_REQUIRE(years{ 1 } == months{ 12 });
}

} // morpheus
