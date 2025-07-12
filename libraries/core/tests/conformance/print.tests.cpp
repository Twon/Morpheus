#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conformance/print.hpp"
#include "morpheus/temp_file.hpp"

#include <catch2/catch_test_macros.hpp>

#include <string>

struct Coordinate
{
    int x;
    int y;
};

template <>
struct morpheus::fmt_ns::formatter<Coordinate> : morpheus::fmt_ns::formatter<std::string>
{
    template <typename Context>
    constexpr auto format(Coordinate const& value, Context& context) const
    {
        return morpheus::fmt_ns::format_to(context.out(), "{{x={},y={}}}", value.x, value.y);
    }
};


namespace morpheus
{

TEST_CASE("Ensure print is supported and working", "[morpheus.conformance.print]")
{
    GIVEN("A capture to file")
    {
        TempFile temp;

        WHEN("Using std::print to write output")
        {
            // Ensure time zones work
            print_ns::print(temp.getFile(), "{2} {1} {0}", true, 3.14, 100);

            THEN("Expect the variables wrote to the stream in the specified order")
            {
                REQUIRE(temp.contents() == "100 3.14 true");
            }
        }
    }
}

TEST_CASE("Ensure print is works with formatter customisations", "[morpheus.conformance.print.std_fmt_interop]")
{
    GIVEN("A capture to file")
    {
        TempFile temp;

        WHEN("Using std::print to write output")
        {
            Coordinate coord{50, 100};

            // Ensure time zones work
            print_ns::print(temp.getFile(), "{}", coord);

            THEN("Expect the variables wrote to the stream in the specified order")
            {
                REQUIRE(temp.contents() == "{50, 100}");
            }
        }
    }
}

} // morpheus
