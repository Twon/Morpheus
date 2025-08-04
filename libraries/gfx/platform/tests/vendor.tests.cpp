#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/gfx/platform/vendor.hpp"

#include <catch2/catch_test_macros.hpp>
#include <magic_enum/magic_enum.hpp>

#include <array>
#include <optional>
#include <utility>

namespace morpheus::gfx
{

TEST_CASE("Ensure image accessors", "[morpheus.gfx.vendor.vendorFromPciId]")
{
    constexpr auto vendors = magic_enum::enum_values<Vendor>();

    for (auto const& vendor : ranges::drop_view{vendors, 1})
    {
        REQUIRE(vendorFromPciId(std::to_underlying(vendor)) == vendor);
    }
}

}
