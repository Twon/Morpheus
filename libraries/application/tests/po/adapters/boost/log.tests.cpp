#include "morpheus/application/po/adapters/boost/log.hpp"
#include "morpheus/application/po/options.hpp"
#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/logging.hpp"
#include "morpheus/redirect_stream.hpp"

#include <boost/log/trivial.hpp>
#include <catch2/catch_test_macros.hpp>
#include <iostream>

namespace morpheus::application::po
{

struct BoostLogFixture
{
    LoggingFixture disableLogging;
    RedirectStream captureCout = RedirectStream(std::cout);
    RedirectStream captureCerr = RedirectStream(std::cerr);
};

struct Logging
{
    boost::log::trivial::severity_level logLevel = boost::log::trivial::info;

    void addOptions(boost::program_options::options_description& options)
    {
        namespace po = boost::program_options;
        // clang-format off
        options.add_options()
            ("log-level", po::value(&logLevel)->default_value(logLevel), "The level most permissive level of logging to allow into the log file.");
        // clang-format on
    }
};

TEST_CASE_METHOD(BoostLogFixture, "Test parsing of boost log types as program options", "[morpheus.application.po.adapters.boost.log]")
{
    using namespace boost::log::trivial;

    SECTION("Ensure valid value parse correctly")
    {
        auto getLogLevel = [](std::string_view param)
        {
            Logging logging{};
            std::array cliOptions = { "dummyProgram.exe", "--log-level", param.data() };
            auto const result = parseProgramOptions(cliOptions.size(), cliOptions.data(), HelpDocumentation{}, logging);
            REQUIRE(!result);
            return logging.logLevel;
        };

        REQUIRE(getLogLevel("trace") == trace);
        REQUIRE(getLogLevel("TRACE") == trace);
        REQUIRE(getLogLevel("tRaCe") == trace);
        REQUIRE(getLogLevel("debug") == debug);
        REQUIRE(getLogLevel("DEBUG") == debug);
        REQUIRE(getLogLevel("dEbUg") == debug);
        REQUIRE(getLogLevel("info") == info);
        REQUIRE(getLogLevel("INFO") == info);
        REQUIRE(getLogLevel("iNFo") == info);
        REQUIRE(getLogLevel("warning") == warning);
        REQUIRE(getLogLevel("WARNING") == warning);
        REQUIRE(getLogLevel("wArNiNg") == warning);
        REQUIRE(getLogLevel("error") == error);
        REQUIRE(getLogLevel("ERROR") == error);
        REQUIRE(getLogLevel("ErRoR") == error);
        REQUIRE(getLogLevel("fatal") == fatal);
        REQUIRE(getLogLevel("FATAL") == fatal);
        REQUIRE(getLogLevel("FaTaL") == fatal);
    }
    SECTION("Ensure invalid value parse correctly")
    {
        std::array cliOptions = { "dummyProgram.exe", "--log-level", "invalid"};
        Logging logging;
        auto const result = parseProgramOptions(cliOptions.size(), cliOptions.data(), HelpDocumentation{}, logging);
        REQUIRE(result);
    }
}

} // namespace morpheus::application::po
