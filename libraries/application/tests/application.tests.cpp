#include "morpheus/application/application.hpp"
#include "morpheus/application/po/config.hpp"
#include "morpheus/logging.hpp"

#include <boost/log/trivial.hpp>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_tostring.hpp>

#include <array> 
#include <filesystem> 

namespace morpheus::application::po
{

TEST_CASE_METHOD(LoggingFixture, "Ensure application parse common parameters", "[morpheus.application.application.parameters]")
{
    GIVEN("A common application parameters")
    {
        std::array const cliOptions = {"dummyProgram.exe", "--logging-enabled", "true", "--log-append", "false", "--log-level", "debug", "--logfile-path", "."};
        WHEN("Parsing valid parameters")
        {
            Application application(static_cast<int>(cliOptions.size()), cliOptions.data());

            THEN("Expect no error results and valid values extracted")
            {
                REQUIRE(application.getConfig().loggingEnabled == true);
                REQUIRE(application.getConfig().logAppend == false);
                REQUIRE(application.getConfig().logLevel == boost::log::trivial::debug);
                REQUIRE(application.getConfig().logFilePath == ".");
            }
        }
    }
}

} // namespace morpheus::application::po
