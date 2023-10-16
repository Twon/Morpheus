#include "morpheus/application/po/config.hpp"
#include "morpheus/application/po/options.hpp"

#include <catch2/catch_test_macros.hpp>

#include <array>

namespace morpheus::application::po
{

TEST_CASE("Ensure options parsing of standard application config", "[morpheus.application.po.config]")
{
    GIVEN("A type supporting addOptions")
    {
        Config confg;

        WHEN("Parsing valid parameters")
        {
            std::array const cliOptions = { "dummyProgram.exe", "--logging-enabled", "true", "--log-append", "false", "--log-level", "debug", "--logfile-path", "." };
            auto const result = parseProgramOptions(static_cast<int>(cliOptions.size()), cliOptions.data(), HelpDocumentation{}, confg);

            THEN("Expect no error results and valid values extracted")
            {
                REQUIRE(!result);
                REQUIRE(confg.loggingEnabled == true);
                REQUIRE(confg.logAppend == false);
                REQUIRE(confg.logLevel == boost::log::trivial::debug);
                REQUIRE(confg.logFilePath == ".");
            }
        }
    }
}

}
