#include "morpheus/gfx/platform/monitor.hpp"

#include <catch2/catch_test_macros.hpp>


namespace morpheus::gfx
{


TEST_CASE("Ensure image accessors", "[morpheus.gfx.monitor.constructors]")
{
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
        constexpr std::string_view name = "Default Monitor";
        constexpr Monitor::PixelDiff x = 100;
        constexpr Monitor::PixelDiff y = 200;
        constexpr Monitor::Pixels width = 600;
        constexpr Monitor::Pixels height = 800;
        constexpr bool primary = true;
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
        Monitor monitor1("Monitor 1", 100, 200, 600, 800, true);
        Monitor monitor2(monitor1);
        REQUIRE(monitor2.startX() == monitor1.startX());
        REQUIRE(monitor2.startY() == monitor1.startY());
        REQUIRE(monitor2.width() == monitor1.width());
        REQUIRE(monitor2.height() == monitor1.height());
        REQUIRE(monitor2.primary() == monitor1.primary());
    }
    SECTION("Move constructor")
    {
        Monitor monitor1("Monitor 1", 100, 200, 600, 800, true);
        Monitor monitor2(std::move(monitor1));
        REQUIRE(monitor2.startX() == 100);
        REQUIRE(monitor2.startY() == 200);
        REQUIRE(monitor2.width() == 600);
        REQUIRE(monitor2.height() == 800);
        REQUIRE(monitor2.primary() == true);
    }
}

TEST_CASE("Ensure image accessors", "[morpheus.gfx.monitor.assignment]")
{
    SECTION("Copy assignment operator")
    {
        Monitor monitor1("Monitor 1", 100, 200, 600, 800, true);
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
        Monitor monitor1("Monitor 1", 100, 200, 600, 800, true);
        Monitor monitor2;
        monitor2 = std::move(monitor1);
        REQUIRE(monitor2.startX() == 100);
        REQUIRE(monitor2.startY() == 200);
        REQUIRE(monitor2.width() == 600);
        REQUIRE(monitor2.height() == 800);
        REQUIRE(monitor2.primary() == true);
    }
}
/*
TEST_CASE("Ensure image accessors", "[morpheus.gfx.monitor.comparison]")
{
    SECTION("Comparison operator")
    {
        Monitor monitor1("Monitor 1", 100, 200, 600, 800, true);
        Monitor monitor2("Monitor 2", 100, 200, 600, 800, true);
        REQUIRE(monitor1 == monitor2);
        monitor2 = Monitor("Monitor 3", 100, 200, 600, 800, false);
        REQUIRE(monitor1 != monitor2);
    }
    SECTION("Less than operator")
    {
        Monitor monitor1("Monitor 1", 100, 200, 600, 800, true);
        Monitor monitor2("Monitor 2", 100, 200, 600, 800, true);
        REQUIRE(monitor1 < monitor2);
        monitor2 = Monitor("Monitor 3", 100, 200, 600, 800, false);
        REQUIRE(monitor1 > monitor2);
    }
    SECTION("Greater than operator")
    {
        Monitor monitor1("Monitor 1", 100, 200, 600, 800, true);
        Monitor monitor2("Monitor 2", 100, 200, 600, 800, true);
        REQUIRE(monitor1 > monitor2);
        monitor2 = Monitor("Monitor 3", 100, 200, 600, 800, false);
        REQUIRE(monitor1 < monitor2);
    }
    SECTION("Less than or equal to operator")
    {
        Monitor monitor1("Monitor 1", 100, 200, 600, 800, true);
        Monitor monitor2("Monitor 2", 100, 200, 600, 800, true);
        REQUIRE(monitor1 <= monitor2);
        monitor2 = Monitor("Monitor 3", 100, 200, 600, 800, false);
        REQUIRE(monitor1 >= monitor2);
    }
    SECTION("Greater than or equal to operator")
    {
        Monitor monitor1("Monitor 1", 100, 200, 600, 800, true);
        Monitor monitor2("Monitor 2", 100, 200, 600, 800, true);
        REQUIRE(monitor1 >= monitor2);
        monitor2 = Monitor("Monitor 3", 100, 200, 600, 800, false);
        REQUIRE(monitor1 <= monitor2);
    }
    SECTION("Name accessor")
    {
        Monitor monitor("Monitor 1", 100, 200, 600, 800, true);
        REQUIRE(monitor.name() == "Monitor 1");
    }
    SECTION("Width accessor")
    {
        Monitor monitor("Monitor 1", 100, 200, 600, 800, true);
        REQUIRE(monitor.width() == 600);
    }
    SECTION("Height accessor")
    {
        Monitor monitor("Monitor 1", 100, 200, 600, 800, true);
        REQUIRE(monitor.height() == 800);
    }
    SECTION("StartX accessor")
    {
        Monitor monitor("Monitor 1", 100, 200, 600, 800, true);
        REQUIRE(monitor.startX() == 100);
    }
    SECTION("StartY accessor")
    {
        Monitor monitor("Monitor 1", 100, 200, 600, 800, true);
        REQUIRE(monitor.startY() == 200);
    }
    SECTION("Primary accessor")
    {
        Monitor monitor("Monitor 1", 100, 200, 600, 800, true);
        REQUIRE(monitor.primary() == true);
    }
    SECTION("Primary accessor false")
    {
        Monitor monitor("Monitor 1", 100, 200, 600, 800, false);
        REQUIRE(monitor.primary() == false);
    }
    SECTION("Primary accessor default")
    {
        Monitor monitor("Monitor 1", 100, 200, 600, 800);
        REQUIRE(monitor.primary() == false);
    }
    SECTION("Primary accessor default true")
    {
        Monitor monitor("Monitor 1", 100, 200, 600, 800, true);
        REQUIRE(monitor.primary() == true);
    }
    SECTION("Primary accessor default false")
    {
        Monitor monitor("Monitor 1", 100, 200, 600, 800, false);
        REQUIRE(monitor.primary() == false);
    }
    SECTION("Primary accessor default empty")
    {
        Monitor monitor;
        REQUIRE(monitor.primary() == false);
    }
    SECTION("Primary accessor default empty true")
    {
        Monitor monitor;
        monitor = Monitor("Monitor 1", 100, 200, 600, 800, true);
        REQUIRE(monitor.primary() == true);
    }
}
*/

}
