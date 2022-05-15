#pragma once

#include <core/gfx/render_system.hpp>
#include <vulkan/adapter.hpp>
#include <vulkan/version.hpp>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>

#include <string_view>
#include <tuple>
#include <vector>

namespace morpheus::gfx::vulkan
{

/*! \class RenderSystem
        Rendering system abstraction based upon the Vulkan graphics API.
 */
class RenderSystem : public gfx::render_system {
public:
    RenderSystem(std::string_view const appName, std::string_view const engineName);
    virtual ~RenderSystem() override;

    auto const& adapters() const { return mAdapters; }
private:
    vk::raii::Context mContext; /// Vulkan context including loader.
    vk::raii::Instance mInstance; /// Vulkan instance stores all per instance state.
    Version mVulkanVersion; /// The instance version of Vulkan available.
    std::vector<vk::ExtensionProperties> mAvailableExtensions; /// The available Vulkan extension properties.
    std::vector<vk::LayerProperties> mAvailableLayers; /// The available Vulkan layer properties.
    AdapterList mAdapters;
};

} // namespace morpheus::gfx::vulkan
