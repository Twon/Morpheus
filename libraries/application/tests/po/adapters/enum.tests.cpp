#include "morpheus/application/application.hpp"
#include "morpheus/application/po/adapters/enum.hpp"

#include <catch2/catch_test_macros.hpp>

#include <array>
#include <cstdint>
#include <string_view>

namespace morpheus::application::po
{

enum class Drink : std::uint32_t
{
    Coke,
    Pepsi,
    Tango,
    Fanta
};

struct Preferences
{
    Drink drink;

    void addOptions(boost::program_options::options_description& options)
    {
        namespace po = boost::program_options;
        // clang-format off
        options.add_options()
            ("drink", po::value(&drink), "The type of drink the user would like.");
        // clang-format on
    }
};

TEST_CASE("Test parsing of enums as options", "[morpheus.application.po.adapters.enum]")
{
    SECTION("Ensure valid value parse correctly")
    {
        auto getDrink = [](std::string_view param)
        {
            Preferences  preferences{};
            std::array cliOptions = {"dummyProgram.exe", "--drink", param.data()};
            auto const result = parseProgramOptions(static_cast<int>(cliOptions.size()), cliOptions.data(), HelpDocumentation{}, preferences);
            REQUIRE(!result);
            return preferences.drink;
        };

        auto const exeLocation = boost::dll::program_location().parent_path();
        REQUIRE(getDrink("Coke") == Drink::Coke);
        REQUIRE(getDrink("Pepsi") == Drink::Pepsi);
        REQUIRE(getDrink("Tango") == Drink::Tango);
        REQUIRE(getDrink("Fanta") == Drink::Fanta);
    }
    SECTION("Ensure invalid value parse correctly")
    {
        std::array cliOptions = {"dummyProgram.exe", "--drink", "invalid" };
        Preferences preferences{};
        auto const result = parseProgramOptions(static_cast<int>(cliOptions.size()), cliOptions.data(), HelpDocumentation{}, preferences);
        REQUIRE(result);
    }
}

} // namespace morpheus::application::po
