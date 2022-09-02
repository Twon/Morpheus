#include "vulkan/adapter.hpp"
#include "core/base/assert.hpp"
#include "core/conformance/ranges.hpp"

namespace morpheus::gfx::vulkan
{

Adapter::Adapter(vk::raii::PhysicalDevice&& physicalDevice)
:   mPhysicalDevice(std::move(physicalDevice))
{
}

[[nodiscard]] Vendor Adapter::getVendor() const noexcept
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
