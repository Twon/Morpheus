#include "morpheus/gfx/platform/monitor.hpp"

#include <catch2/catch_test_macros.hpp>

namespace morpheus::gfx
{

TEST_CASE("Ensure monitors construct", "[morpheus.gfx.monitor.constructors]")
{
    constexpr std::string_view name = "Default Monitor";
    constexpr Monitor::PixelDiff x = 100;
    constexpr Monitor::PixelDiff y = 200;
    constexpr Monitor::Pixels width = 600;
    constexpr Monitor::Pixels height = 800;
    constexpr bool primary = true;

    SECTION("Default constructor")
    {
        Monitor const monitor;
        REQUIRE(monitor.startX() == 0);
        REQUIRE(monitor.startY() == 0);
        REQUIRE(monitor.width() == 0);
        REQUIRE(monitor.height() == 0);
        REQUIRE(monitor.primary() == false);
    }
    SECTION("Constructor with parameters")
    {
        Monitor const monitor(name, x, y, width, height, primary);
        REQUIRE(monitor.name() == name);
        REQUIRE(monitor.startX() == x);
        REQUIRE(monitor.startY() == y);
        REQUIRE(monitor.width() == width);
        REQUIRE(monitor.height() == height);
        REQUIRE(monitor.primary() == primary);
    }
    SECTION("Copy constructor")
    {
        Monitor const monitor1(name, x, y, width, height, primary);
        Monitor const monitor2(monitor1);
        REQUIRE(monitor2.startX() == monitor1.startX());
        REQUIRE(monitor2.startY() == monitor1.startY());
        REQUIRE(monitor2.width() == monitor1.width());
        REQUIRE(monitor2.height() == monitor1.height());
        REQUIRE(monitor2.primary() == monitor1.primary());
    }
    SECTION("Move constructor")
    {
        Monitor const monitor1(name, x, y, width, height, primary);
        Monitor const monitor2(std::move(monitor1));
        REQUIRE(monitor2.name() == name);
        REQUIRE(monitor2.startX() == x);
        REQUIRE(monitor2.startY() == y);
        REQUIRE(monitor2.width() == width);
        REQUIRE(monitor2.height() == height);
        REQUIRE(monitor2.primary() == primary);
    }
}

TEST_CASE("Ensure monitor assign correctly", "[morpheus.gfx.monitor.assignment]")
{
    constexpr std::string_view name = "Default Monitor";
    constexpr Monitor::PixelDiff x = 100;
    constexpr Monitor::PixelDiff y = 200;
    constexpr Monitor::Pixels width = 600;
    constexpr Monitor::Pixels height = 800;
    constexpr bool primary = true;

    SECTION("Copy assignment operator")
    {
        Monitor const monitor1(name, x, y, width, height, primary);
        Monitor monitor2;
        monitor2 = monitor1;
        REQUIRE(monitor2.startX() == monitor1.startX());
        REQUIRE(monitor2.startY() == monitor1.startY());
        REQUIRE(monitor2.width() == monitor1.width());
        REQUIRE(monitor2.height() == monitor1.height());
        REQUIRE(monitor2.primary() == monitor1.primary());
    }
    SECTION("Move assignment operator")
    {
        Monitor const monitor1(name, x, y, width, height, primary);
        Monitor monitor2;
        monitor2 = std::move(monitor1);
        REQUIRE(monitor2.name() == name);
        REQUIRE(monitor2.startX() == x);
        REQUIRE(monitor2.startY() == y);
        REQUIRE(monitor2.width() == width);
        REQUIRE(monitor2.height() == height);
        REQUIRE(monitor2.primary() == primary);
    }
}

TEST_CASE("Ensure image accessors", "[morpheus.gfx.monitor.comparison]")
{
    constexpr std::string_view name = "Default Monitor";
    constexpr Monitor::PixelDiff x = 100;
    constexpr Monitor::PixelDiff y = 200;
    constexpr Monitor::Pixels width = 600;
    constexpr Monitor::Pixels height = 800;
    constexpr bool primary = true;

    SECTION("Comparison operator")
    {
        Monitor const monitor1(name, x, y, width, height, primary);
        REQUIRE(monitor1 == monitor1);
        Monitor const monitor2 = Monitor("Monitor 2", x, y, width, height, false);
        REQUIRE(monitor1 != monitor2);
    }
    SECTION("Less than operator")
    {
        Monitor const monitor1("Monitor 1", x, y, width, height, true);
        Monitor const monitor2("Monitor 2", x, y, width, height, true);
        REQUIRE(monitor1 < monitor2);
        Monitor const monitor3 = Monitor("Monitor 3", x, y, width, height, false);
        REQUIRE(monitor3 > monitor2);
    }
    SECTION("Greater than operator")
    {
        Monitor const monitor1("Monitor 1", x, y, width, height, true);
        Monitor const monitor2("Monitor 2", x, y, width, height, true);
        REQUIRE(monitor2 > monitor1);
        Monitor const monitor3 = Monitor("Monitor 3", x, y, width, height, false);
        REQUIRE(monitor2 < monitor3);
    }
    SECTION("Less than or equal to operator")
    {
        Monitor const monitor1("Monitor 1", x, y, width, height, true);
        Monitor const monitor2("Monitor 2", x, y, width, height, true);
        REQUIRE(monitor1 <= monitor2);
        REQUIRE(monitor2 <= monitor2);
        Monitor const monitor3 = Monitor("Monitor 3", x, y, width, height, false);
        REQUIRE(monitor3 >= monitor2);
        REQUIRE(monitor3 >= monitor3);
    }
    SECTION("Greater than or equal to operator")
    {
        Monitor const monitor1("Monitor 1", x, y, width, height, true);
        Monitor const monitor2("Monitor 2", x, y, width, height, true);
        REQUIRE(monitor2 >= monitor2);
        REQUIRE(monitor2 >= monitor2);
        Monitor const monitor3 = Monitor("Monitor 3", x, y, width, height, false);
        REQUIRE(monitor2 <= monitor2);
        REQUIRE(monitor2 <= monitor3);
    }
}

TEST_CASE("Ensure format is supported for monitors", "[morpheus.gfx.monitor.fmt]")
{
    constexpr std::string_view name = "Main Display";
    constexpr Monitor::PixelDiff x = 100;
    constexpr Monitor::PixelDiff y = 200;
    constexpr Monitor::Pixels width = 600;
    constexpr Monitor::Pixels height = 800;
    constexpr bool primary = true;
    Monitor const monitor(name, x, y, width, height, primary);
    REQUIRE(conf::fmt::format("{}", monitor) ==
            conf::fmt::format("{{name={},{{x={},y={}}},{{width={},height={}}},primary={}}}", name, x, y, width, height, primary));
}

} // namespace morpheus::gfx
