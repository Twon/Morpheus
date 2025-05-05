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
        Monitor monitor;
        REQUIRE(monitor.startX() == 0);
        REQUIRE(monitor.startY() == 0);
        REQUIRE(monitor.width() == 0);
        REQUIRE(monitor.height() == 0);
        REQUIRE(monitor.primary() == false);
    }
    SECTION("Constructor with parameters")
    {
        Monitor monitor(name, x, y, width, height, primary);
        REQUIRE(monitor.name() == name);
        REQUIRE(monitor.startX() == x);
        REQUIRE(monitor.startY() == y);
        REQUIRE(monitor.width() == width);
        REQUIRE(monitor.height() == height);
        REQUIRE(monitor.primary() == primary);
    }
    SECTION("Copy constructor")
    {
        Monitor monitor1(name, x, y, width, height, primary);
        Monitor monitor2(monitor1);
        REQUIRE(monitor2.startX() == monitor1.startX());
        REQUIRE(monitor2.startY() == monitor1.startY());
        REQUIRE(monitor2.width() == monitor1.width());
        REQUIRE(monitor2.height() == monitor1.height());
        REQUIRE(monitor2.primary() == monitor1.primary());
    }
    SECTION("Move constructor")
    {
        Monitor monitor1(name, x, y, width, height, primary);
        Monitor monitor2(std::move(monitor1));
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
        Monitor monitor1(name, x, y, width, height, primary);
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
        Monitor monitor1(name, x, y, width, height, primary);
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
        Monitor monitor1(name, x, y, width, height, primary);
        REQUIRE(monitor1 == monitor1);
        Monitor monitor2 = Monitor("Monitor 2", x, y, width, height, false);
        REQUIRE(monitor1 != monitor2);
    }
    SECTION("Less than operator")
    {
        Monitor monitor1("Monitor 1", x, y, width, height, true);
        Monitor monitor2("Monitor 2", x, y, width, height, true);
        REQUIRE(monitor1 < monitor2);
        Monitor monitor3 = Monitor("Monitor 3", x, y, width, height, false);
        REQUIRE(monitor3 > monitor2);
    }
    SECTION("Greater than operator")
    {
        Monitor monitor1("Monitor 1", x, y, width, height, true);
        Monitor monitor2("Monitor 2", x, y, width, height, true);
        REQUIRE(monitor2 > monitor1);
        Monitor monitor3 = Monitor("Monitor 3", x, y, width, height, false);
        REQUIRE(monitor2 < monitor3);
    }
    SECTION("Less than or equal to operator")
    {
        Monitor monitor1("Monitor 1", x, y, width, height, true);
        Monitor monitor2("Monitor 2", x, y, width, height, true);
        REQUIRE(monitor1 <= monitor2);
        REQUIRE(monitor2 <= monitor2);
        Monitor monitor3 = Monitor("Monitor 3", x, y, width, height, false);
        REQUIRE(monitor3 >= monitor2);
        REQUIRE(monitor3 >= monitor3);
    }
    SECTION("Greater than or equal to operator")
    {
        Monitor monitor1("Monitor 1", x, y, width, height, true);
        Monitor monitor2("Monitor 2", x, y, width, height, true);
        REQUIRE(monitor2 >= monitor2);
        REQUIRE(monitor2 >= monitor2);
        Monitor monitor3 = Monitor("Monitor 3", x, y, width, height, false);
        REQUIRE(monitor2 <= monitor2);
        REQUIRE(monitor2 <= monitor3);
    }
}

TEST_CASE("Ensure format is supported for monitors", "[morpheus.gfx.monitor.fmt]")
{
    Monitor monitor("Main Display", 100, 200, 600, 800, true);
    REQUIRE(fmt_ns::format("{}", monitor) == "{name=Main Display,{x=100,y=200},{width=600,height=800},primary=true}");
}

}
