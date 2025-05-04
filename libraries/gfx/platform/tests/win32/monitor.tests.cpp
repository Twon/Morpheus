#include "morpheus/gfx/platform/win32/monitor.hpp"

#include <catch2/catch_test_macros.hpp>

namespace morpheus::gfx::win32
{

TEST_CASE("MacMonitorEnumerator returns at least one screen", "[morpheus.gfx.win32.monitor]")
{
    const auto monitors = enumerateMonitors();
    const auto monitorsCollection = ranges::to<std::vector>(monitors);
    REQUIRE(!monitorsCollection.empty());
}

} // namespace morpheus::gfx::win32
