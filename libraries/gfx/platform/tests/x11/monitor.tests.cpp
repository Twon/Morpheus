#include "morpheus/gfx/platform/x11/monitor.hpp"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>

namespace morpheus::gfx::x11
{

TEST_CASE("enumerateMonitors for x11 returns at least one screen", "[morpheus.gfx.x11.monitor]")
{
    const auto monitors = enumerateMonitors();
    std::vector<Monitor> monitorsCollection;
    ranges::copy(monitors.begin(), monitors.end(), std::back_inserter(monitorsCollection));
    REQUIRE(!monitorsCollection.empty());
}

} // namespace morpheus::gfx::x11
