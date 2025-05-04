#include "morpheus/gfx/platform/x11/monitor.hpp"

#include <catch2/catch_test_macros.hpp>


namespace morpheus::gfx::x11
{

TEST_CASE("MacMonitorEnumerator returns at least one screen", "[morpheus.gfx.x11.monitor]")
{
    const auto monitors = enumerateMonitors();
    const auto monitorsCollection = ranges::to<std::vector>(monitors);
    REQUIRE(!monitorsCollection.empty());
}

} // namespace morpheus::gfx::x11
