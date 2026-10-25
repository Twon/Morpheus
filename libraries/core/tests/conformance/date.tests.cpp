#include "morpheus/core/conformance/date.hpp"

#include <catch2/catch_test_macros.hpp>

namespace morpheus
{

TEST_CASE("Ensure date library is supported and working", "[morpheus.conformance.date]")
{
    using conf::date::day;
    using conf::date::days;
    using conf::date::locate_zone;
    using conf::date::month;
    using conf::date::months;
    using conf::date::weeks;
    using conf::date::year;
    using conf::date::year_month_day;
    using conf::date::years;

    // Ensure time zones work
    REQUIRE(conf::date::locate_zone("Europe/London"));

    STATIC_REQUIRE((year{2022} / month{11} / day{8}) == year_month_day(year{2022}, month{11}, day{8}));
    STATIC_REQUIRE(weeks{1} == days{7});
    STATIC_REQUIRE(years{1} == months{12});
}

} // namespace morpheus
