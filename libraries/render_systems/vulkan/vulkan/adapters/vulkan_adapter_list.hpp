#pragma once

#include <core/gfx/adapters/adapter.hpp>

#include <vulkan/vulkan_raii.hpp>

#include <vector>

namespace morpheus::gfx::vulkan
{

/*! \class adapter_list

 */
/*class AdapterList {
public:

    AdapterList(vk::raii::Instance const& instance) 
    :   mInstance(instance)
    ,   mPhysicalDevices(instance.enumeratePhysicalDevices())
    {}
    
    /// \name Life cycle
    ///@{

    ///@}

private:
    using PhysicalDevices = std::vector<vk::raii::PhysicalDevice>;

    vk::raii::Instance const& mInstance; /// Vulkan instance stores all per instance state.   
    PhysicalDevices mPhysicalDevices; /// All physical devices on the target host.
    vk::PhysicalDevice mPhysicalDevice; /// Physical device (GPU) that Vulkan will use.
};*/

} // namespace morpheus::gfx::vulkan
