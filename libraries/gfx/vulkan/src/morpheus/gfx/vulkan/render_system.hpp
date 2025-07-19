#pragma once

#include <morpheus/core/conformance/expected.hpp>
#include <morpheus/gfx/platform/render_system.hpp>
#include <morpheus/gfx/vulkan/adapter.hpp>
#include <morpheus/gfx/vulkan/version.hpp>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>

#include <string_view>
#include <tuple>
#include <vector>

namespace morpheus::gfx::vulkan
{

/// \class RenderSystem
///     Rendering system abstraction based upon the Vulkan graphics API.
class RenderSystem : public gfx::RenderSystem {
public:
    RenderSystem(std::string_view const appName, std::string_view const engineName);

    RenderSystem(RenderSystem const&) = delete;
    RenderSystem& operator=(RenderSystem const&) = delete;

    RenderSystem(RenderSystem&&) = default;
    RenderSystem& operator=(RenderSystem&&) = default;

    /// Get the name of the underlying graphic API.
    [[nodiscard]] static auto getGraphicsApi() noexcept -> std::string_view { return "Vulkan"; }

    [[nodiscard]] static auto create() -> exp_ns::expected<RenderSystem, std::string>;


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
