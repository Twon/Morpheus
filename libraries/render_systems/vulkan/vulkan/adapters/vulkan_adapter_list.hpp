#pragma once

#include <core/gfx/adapters/adapter.hpp>

#include <vector>

namespace morpheus::gfx::vulkan
{

/*! \class adapter_list

 */
class adapter_list {
public:

    adapter_list();
    
    /// \name Life cycle
    ///@{

    ///@}

private:
    using PhysicalDevices = std::vector<vk::PhysicalDevice>;

    vk::Instance mInstance; /// Vulkan instance stores all per instance state.
    PhysicalDevices mPhysicalDevices; /// All physical devices on the target host.
    vk::PhysicalDevice mPhysicalDevice; /// Physical device (GPU) that Vulkan will use.
};

} // namespace morpheus::gfx::vulkan
