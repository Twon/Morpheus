#include "vulkan/adapter.hpp"
#include "core/conformance/ranges.hpp"

namespace morpheus::gfx::vulkan
{

Adapter::Adapter(vk::raii::PhysicalDevice&& physicalDevice)
:   mPhysicalDevice(std::move(physicalDevice))
{
}

std::string Adapter::getName() const
{
    return mPhysicalDevice.getProperties().deviceName;
}

AdapterList enumerateAdapters(vk::raii::Instance const& instance)
{    
    AdapterList adapters;
    ranges::move(instance.enumeratePhysicalDevices(), ranges::back_inserter(adapters));
    return adapters;
}

} // namespace morpheus::gfx::vulkan
