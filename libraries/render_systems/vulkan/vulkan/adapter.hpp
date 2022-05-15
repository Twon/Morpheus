#pragma once

#include "vulkan/video_mode.hpp"
#include "core/platform.hpp"

#include <vulkan/vulkan_raii.hpp>

#include <string>
#include <vector>

namespace morpheus::gfx::vulkan
{

/// \class Adapter
///     Describes an available graphic hardware devices on the target platform.
class Adapter {
public:
    /// \name Life cycle
    ///@{
    Adapter(vk::raii::PhysicalDevice&& physicalDevice);
    ///@}

    std::string getName() const;

    
private:
    vk::raii::PhysicalDevice mPhysicalDevice;
};

using AdapterList = std::vector<Adapter>;

AdapterList enumerateAdapters(vk::raii::Instance const& instance);

} // namespace morpheus::gfx::vulkan
