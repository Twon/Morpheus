#include "morpheus/application/application.hpp"
#include "morpheus/application/po/adapters/scannable.hpp"
#include "morpheus/logging.hpp"

#include <catch2/catch_test_macros.hpp>

#include <array>
#include <compare>
#include <cstdint>
#include <string_view>
#include <tuple>

struct Coordinates
{
    double x = 0.0;
    double y = 0.0;

    auto operator<=>(Coordinates const&) const = default;
};

template <>
struct morpheus::scan_ns::scanner<Coordinates> : morpheus::scan_ns::scanner<std::string>
{
    template <typename Context>
    auto scan(Coordinates& val, Context& ctx) const -> morpheus::scan_ns::scan_expected<typename Context::iterator>
    {
        return morpheus::scan_ns::scan<int, double>(ctx.range(), "[{}, {}]")
            .transform(
                [&val](auto const& result)
                {
                    std::tie(val.x, val.y) = result.values();
                    return result.begin();
                });
    }
};

namespace morpheus::application::po
{

struct Location
{
    Coordinates coordinates;

    void addOptions(boost::program_options::options_description& options)
    {
        namespace po = boost::program_options;
        // clang-format off
        options.add_options()
            ("coordinates", po::value(&coordinates), "The 2-dimensional coordinates of the location.");
        // clang-format on
    }
};

TEST_CASE_METHOD(LoggingFixture, "Test parsing of scannable as options", "[morpheus.application.po.adapters.scannable]")
{
    SECTION("Ensure valid value parse correctly")
    {
        auto getCoordinates = [](std::string_view param)
        {
            Location location{};
            std::array cliOptions = {"dummyProgram.exe", "--coordinates", param.data()};
            auto const result = parseProgramOptions(static_cast<int>(cliOptions.size()), cliOptions.data(), HelpDocumentation{}, location);
            REQUIRE(!result);
            return location.coordinates;
        };

        REQUIRE(getCoordinates("[1, 97]") == Coordinates {1.0, 97.0});
    }
    SECTION("Ensure invalid value parse correctly")
    {
        std::array cliOptions = {"dummyProgram.exe", "--coordinates", "invalid"};
        Location location{};
        auto const result = parseProgramOptions(static_cast<int>(cliOptions.size()), cliOptions.data(), HelpDocumentation{}, location);
        REQUIRE(result);
    }
}

} // namespace morpheus::application::po
