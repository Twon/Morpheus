#include "morpheus/core/base/assert.hpp"
#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/gfx/vulkan/adapter.hpp"

namespace morpheus::gfx::vulkan
{

Adapter::Adapter(vk::raii::PhysicalDevice&& physicalDevice)
    : mPhysicalDevice(std::move(physicalDevice))
{}

[[nodiscard]] Vendor Adapter::vendor() const noexcept
{
    auto const vendor = vendorFromPciId(mPhysicalDevice.getProperties().vendorID);
    MORPHEUS_ASSERT(vendor);
    return *vendor;
}

AdapterList enumerateAdapters(vk::raii::Instance const& instance)
{
    AdapterList adapters;
    ranges::move(instance.enumeratePhysicalDevices(), ranges::back_inserter(adapters));
    return adapters;
}

} // namespace morpheus::gfx::vulkan
