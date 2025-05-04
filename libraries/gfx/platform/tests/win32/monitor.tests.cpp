#include "morpheus/gfx/platform/win32/monitor.hpp"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>

namespace morpheus::gfx::win32
{

TEST_CASE("enumerateMonitors for win32 returns at least one screen", "[morpheus.gfx.win32.monitor]")
{
    const auto monitors = enumerateMonitors();
    std::vector<Monitor> monitorsCollection;
    ranges::copy(monitors.begin(), monitors.end(), std::back_inserter(monitorsCollection));
    REQUIRE(!monitorsCollection.empty());
}

} // namespace morpheus::gfx::win32
