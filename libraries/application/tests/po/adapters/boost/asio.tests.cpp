#include "morpheus/application/po/adapters/boost/asio.hpp"
#include "morpheus/application/po/options.hpp"
#include "morpheus/application/version.hpp"
#include "morpheus/logging.hpp"
#include "morpheus/redirect_stream.hpp"

#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/address_v6.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/value_semantic.hpp>
#include <catch2/catch_test_macros.hpp>

#include <array>
#include <iostream>
#include <optional>
#include <string_view>

namespace morpheus::application::po
{

struct BoostLogFixture
{
    LoggingFixture disableLogging;
    RedirectStream captureCout = RedirectStream(std::cout);
    RedirectStream captureCerr = RedirectStream(std::cerr);
};

struct Address
{
    boost::asio::ip::address ipAddress;

    void addOptions(boost::program_options::options_description& options)
    {
        namespace po = boost::program_options;
        // clang-format off
        options.add_options()
            ("address", po::value(&ipAddress)->required(), "The ip address.");
        // clang-format on
    }
};

TEST_CASE_METHOD(BoostLogFixture, "Test parsing of boost asio address as program options", "[morpheus.application.po.adapters.boost.asio.address]")
{

    SECTION("Ensure valid value parse correctly")
    {
        auto getAddress = [](std::string_view param)
        {
            Address address{};
            std::array cliOptions = {"dummyProgram.exe", "--address", param.data()};
            auto const result = parseProgramOptions(static_cast<int>(cliOptions.size()), cliOptions.data(), HelpDocumentation{}, address);
            REQUIRE(!result);
            return address.ipAddress;
        };

        REQUIRE(getAddress("127.0.0.1") == boost::asio::ip::address_v4::loopback());
        REQUIRE(getAddress("192.168.1.218") == boost::asio::ip::address_v4({192, 168, 1, 218}));
        REQUIRE(getAddress("0:0:0:0:0:0:0:1") == boost::asio::ip::address_v6::loopback());
        REQUIRE(getAddress("fd00::f06b:9ee5:8bfa:666c") ==
                boost::asio::ip::address_v6({0xfd, 0, 0, 0, 0, 0, 0, 0, 0xf0, 0x6b, 0x9e, 0xe5, 0x8b, 0xfa, 0x66, 0x6c}));
    }
    SECTION("Ensure invalid value parse correctly")
    {
        std::array cliOptions = {"dummyProgram.exe", "--address", "invalid"};
        Address address;
        auto const result = parseProgramOptions(static_cast<int>(cliOptions.size()), cliOptions.data(), HelpDocumentation{}, address);
        REQUIRE(result);
    }
}

} // namespace morpheus::application::po
