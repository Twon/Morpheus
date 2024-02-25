#include "morpheus/application/application.hpp"
#include "morpheus/application/po/adapters/std/optional.hpp"
#include "morpheus/logging.hpp"

#include <catch2/catch_test_macros.hpp>

#include <boost/optional.hpp>
#include <boost/program_options.hpp>

#include <optional>
#include <string>

namespace morpheus::application::po
{

struct OptionalConfig
{
    std::optional<std::string> text;
//    boost::optional<std::string> text;

    void addOptions(boost::program_options::options_description& options)
    {
        namespace po = boost::program_options;
        // clang-format off
        options.add_options()
            ("text", po::value(&text), "The optional text value");
        // clang-format on
    }
};

TEST_CASE_METHOD(LoggingFixture, "Test parsing of std optional wrapped type", "[morpheus.application.po.adapters.std.optional]")
{
    SECTION("Ensure unspecified value is null")
    {
        std::array cliOptions = {"dummyProgram.exe", "--text"};
        OptionalConfig options{};
        auto const result = parseProgramOptions(static_cast<int>(cliOptions.size()), cliOptions.data(), HelpDocumentation{}, options);
        REQUIRE(result);
        REQUIRE(!options.text);
    }
    SECTION("Ensure valid value parse correctly")
    {
        std::array cliOptions = {"dummyProgram.exe", "--text", "valid"};
        OptionalConfig options{};
        auto const result = parseProgramOptions(static_cast<int>(cliOptions.size()), cliOptions.data(), HelpDocumentation{}, options);
        REQUIRE(!result);
        REQUIRE(*options.text == "valid");
    }
}

} // namespace morpheus::application::po
