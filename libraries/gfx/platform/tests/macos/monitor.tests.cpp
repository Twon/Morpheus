#include "morpheus/gfx/platform/macos/monitor.hpp"

#include <catch2/catch_test_macros.hpp>

namespace morpheus::gfx::macos
{

TEST_CASE("MacMonitorEnumerator returns at least one screen", "[morpheus.gfx.macos.monitor]")
{
    const auto monitors = enumerateMonitors();
    const auto monitorsCollection = ranges::to<std::vector>(monitors);
    REQUIRE(!monitorsCollection.empty());
}

} // namespace morpheus::gfx::macos
