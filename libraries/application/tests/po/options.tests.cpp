#include "morpheus/application/po/options.hpp"
#include "morpheus/application/version.hpp"
#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/logging.hpp"
#include "morpheus/redirect_stream.hpp"

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/value_semantic.hpp>
#include <catch2/catch_test_macros.hpp>

#include <array>
#include <cstdint>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

namespace morpheus::application::po
{

struct Person
{
    std::string firstName;
    std::string surname;
    std::uint32_t age = 0;
    std::uint32_t yearOfBirth = 0;
    bool alive = false;

    void addOptions(boost::program_options::options_description& options)
    {
        namespace po = boost::program_options;
        // clang-format off
        options.add_options()
            ("first-name,f", po::value(&firstName)->required(), "The persons first name.")
            ("surname,s", po::value(&surname)->required(), "The persons surname.")
            ("age,a", po::value(&age)->required(), "The persons age.")
            ("year-of-birth,y", po::value(&yearOfBirth)->required(), "The persons year of birth.")
            ("alive,x", po::value(&alive)->required(), "Is the persons still alive.");
        // clang-format on
    }
};

auto captureOutput(ranges::contiguous_range auto const& cliOptions, HelpDocumentation msgDetails, CustomProgramOptions auto&... options)
{
    RedirectStream captureStream(std::cout);
    auto const result = parseProgramOptions(static_cast<int>(ranges::size(cliOptions)), ranges::data(cliOptions), msgDetails, options...);
    REQUIRE(result);
    auto const output = captureStream.getOutput();

    auto const findOption = [stdOut = std::move(output)](std::string const optionText)
    {
        auto linesView = stdOut | ranges::views::split('\n') | ranges::views::transform([](auto&& rng) {
            return std::string_view(&*rng.begin(), ranges::distance(rng));
        });

        return ranges::find_if(linesView,
            [optionText](auto const line)
            {
                return line.contains(optionText);
            }
        ) != linesView.end();
    };
    return findOption;
}

TEST_CASE_METHOD(LoggingFixture, "Ensure options parsing of native types works", "[morpheus.application.po.basic_types]")
{
    GIVEN("A type supporting addOptions")
    {
        Person person;

        WHEN("Parsing valid parameters")
        {
            std::array const cliOptions = { "dummyProgram.exe", "--first-name", "John", "--surname", "Doe", "--age", "42", "--year-of-birth", "1980", "--alive", "true" };
            auto const result = parseProgramOptions(static_cast<int>(cliOptions.size()), cliOptions.data(), HelpDocumentation{}, person);

            THEN("Expect no error results and valid values extracted")
            {
                REQUIRE(!result);
                REQUIRE(person.firstName == "John");
                REQUIRE(person.surname == "Doe");
                REQUIRE(person.age == 42);
                REQUIRE(person.yearOfBirth == 1980);
                REQUIRE(person.alive == true);
            }
        }
        WHEN("Parsing invalid parameters because the first parameter is not a program name")
        {
            std::array const cliOptions = {"--first-name", "John", "--surname", "Doe", "--age", "42", "--year-of-birth", "1980", "--alive", "true"};
            // RedirectStream captureErrors(std::cerr); Capture error logging
            auto const result = parseProgramOptions(static_cast<int>(cliOptions.size()), cliOptions.data(), HelpDocumentation{}, person);
            THEN("Expect no error results and valid values extracted")
            {
                REQUIRE(result);
            }
        }
        WHEN("Requesting the help text is displayed")
        {
            std::array const cliOptions = {"dummyProgram.exe", "-h"};
            auto findOption = captureOutput(cliOptions, HelpDocumentation{}, person);
            THEN("Expect output to be successfully prints to screen")
            {
                REQUIRE(findOption("--help"));
                REQUIRE(findOption("--first-name"));
                REQUIRE(findOption("--surname"));
                REQUIRE(findOption("--age"));
                REQUIRE(findOption("--year-of-birth"));
                REQUIRE(findOption("--alive"));
            }
        }
        WHEN("Requesting the help text is displayed when providing a version")
        {
            std::array const cliOptions = {"dummyProgram.exe", "-h"};
            HelpDocumentation helpWithVersion;
            helpWithVersion.version = Version{1, 0, 0};
            auto findOption = captureOutput(cliOptions, helpWithVersion, person);
            THEN("Expect output to be successfully prints to screen with version option")
            {
                REQUIRE(findOption("--help"));
                REQUIRE(findOption("--version"));
                REQUIRE(findOption("--first-name"));
                REQUIRE(findOption("--surname"));
                REQUIRE(findOption("--age"));
                REQUIRE(findOption("--year-of-birth"));
                REQUIRE(findOption("--alive"));
            }
        }
        WHEN("Requesting the help text is displayed with multiple options objects")
        {
            std::array const cliOptions = {"dummyProgram.exe", "-h"};

            struct Extra
            {
                std::string extra;

                void addOptions(boost::program_options::options_description& options)
                {
                    namespace po = boost::program_options;
                    // clang-format off
                    options.add_options()
                        ("extra,e", po::value(&extra)->required(), "An extra field to add to the configuration.");
                    // clang-format on
                }
            } extra;

            auto findOption = captureOutput(cliOptions, HelpDocumentation{}, person, extra);

            THEN("Expect output to be successfully prints to screen with extra parameter")
            {
                REQUIRE(findOption("--help"));
                REQUIRE(findOption("--first-name"));
                REQUIRE(findOption("--surname"));
                REQUIRE(findOption("--age"));
                REQUIRE(findOption("--year-of-birth"));
                REQUIRE(findOption("--alive"));
                REQUIRE(findOption("--extra"));
            }
        }
    }
}

} // namespace morpheus::application::po
