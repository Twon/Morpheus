#pragma once

#include <core/gfx/render_system.hpp>
#include <vulkan/version.hpp>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>

#include <string_view>
#include <tuple>
#include <vector>

namespace morpheus::gfx::vulkan
{

/*! \class render_system
        Rendering system abstraction based upon the Vulkan graphics API.
 */
class render_system : public gfx::render_system {
public:
    render_system(std::string_view const appName, std::string_view const engineName);
    virtual ~render_system() override;

private:
    vk::raii::Context mContext; /// Vulkan context including loader.
    vk::raii::Instance mInstance; /// Vulkan instance stores all per instance state.
    Version mVulkanVersion; /// The instance version of Vulkan available.
    std::vector<vk::ExtensionProperties> mAvailableExtensions; /// The available Vulkan extension properties.
    std::vector<vk::LayerProperties> mAvailableLayers; /// The available Vulkan layer properties.
};

} // namespace morpheus::gfx::vulkan
