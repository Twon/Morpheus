#include "vulkan/adapters/vulkan_adapter.hpp"
#include "core/conformance/ranges.hpp"

namespace morpheus::gfx::vulkan
{

Adapter::Adapter(vk::raii::PhysicalDevice&& physicalDevice)
:   mPhysicalDevice(std::move(physicalDevice))
{
}

AdapterList enumerateAdapters(vk::raii::Instance const& instance)
{    
    AdapterList adapters;
    ranges::move(instance.enumeratePhysicalDevices(), std::back_inserter(adapters));
    return adapters;
}

} // namespace morpheus::gfx::vulkan
