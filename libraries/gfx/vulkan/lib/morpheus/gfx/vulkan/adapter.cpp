#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/gfx/vulkan/adapter.hpp"

#include <libassert/assert.hpp>

namespace morpheus::gfx::vulkan
{

Adapter::Adapter(vk::raii::PhysicalDevice&& physicalDevice)
    : mPhysicalDevice(std::move(physicalDevice))
{}

[[nodiscard]] Vendor Adapter::vendor() const noexcept
{
    // Excluded from code coverage until we figure out how to run GPU tests on CI.
    // LCOV_EXCL_START
    auto const vendor = vendorFromPciId(mPhysicalDevice.getProperties().vendorID);
    DEBUG_ASSERT(vendor, "Must find a valid vendor for the given PCI ID.");
    return *vendor;
    // LCOV_EXCL_STOP
}

AdapterList enumerateAdapters(vk::raii::Instance const& instance)
{
    AdapterList adapters;
    conf::ranges::move(instance.enumeratePhysicalDevices(), conf::ranges::back_inserter(adapters));
    return adapters;
}

} // namespace morpheus::gfx::vulkan
