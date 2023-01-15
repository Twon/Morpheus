#pragma once

#include "morpheus/gfx/vulkan/video_mode.hpp"
#include <morpheus/core/base/platform.hpp>
#include <morpheus/gfx/platform/vendor.hpp>

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

    /// \copydoc morpheus::gfx::Adapter::getId()
    [[nodiscard]] auto getId() const noexcept { return mPhysicalDevice.getProperties().deviceID; }

    /// \copydoc morpheus::gfx::Adapter::getName()
    [[nodiscard]] std::string_view getName() const noexcept { return mPhysicalDevice.getProperties().deviceName; }

    /// \copydoc morpheus::gfx::Adapter::getVendor()
    [[nodiscard]] Vendor getVendor() const noexcept;

    /// Get the video modes allowed on the adapter.
    [[nodiscard]] VideoModeList getVideoModes() const noexcept { return VideoModeList{}; }
    
private:
    vk::raii::PhysicalDevice mPhysicalDevice;
};

using AdapterList = std::vector<Adapter>;

AdapterList enumerateAdapters(vk::raii::Instance const& instance);

} // namespace morpheus::gfx::vulkan
