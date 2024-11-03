#include "morpheus/application/po/config.hpp"
#include "morpheus/application/po/options.hpp"
#include "morpheus/application/version.hpp"

#include <boost/log/trivial.hpp>

#include <catch2/catch_test_macros.hpp>

#include <array>
#include <filesystem>
#include <optional>

namespace morpheus::application::po
{

TEST_CASE("Ensure options parsing of standard application config", "[morpheus.application.po.config]")
{
    GIVEN("A type supporting addOptions")
    {
        Config config;

        WHEN("Parsing valid parameters")
        {
            std::array const cliOptions = { "dummyProgram.exe", "--logging-enabled", "true", "--log-append", "false", "--log-level", "debug", "--logfile-path", "." };
            auto const result = parseProgramOptions(static_cast<int>(cliOptions.size()), cliOptions.data(), HelpDocumentation{}, config);

            THEN("Expect no error results and valid values extracted")
            {
                REQUIRE(!result);
                REQUIRE(config.loggingEnabled == true);
                REQUIRE(config.logAppend == false);
                REQUIRE(config.logLevel == boost::log::trivial::debug);
                REQUIRE(config.logFilePath == ".");
            }
        }
    }
}

}
