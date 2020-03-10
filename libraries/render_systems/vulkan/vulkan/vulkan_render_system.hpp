#pragma once

#include <core/gfx/render_system.hpp>
#include <vulkan/vulkan.h>
#include <vector>

namespace morpheus::gfx::vulkan
{

/*! \class render_system
        Rendering system abstraction based upon the Vulkan graphics API.
 */
class render_system : public gfx::render_system {
public:
    render_system();
    virtual ~render_system() override;

private:
    std::tuple<uint32_t, uint32_t, uint32_t> mVulkanVersion;
    std::vector<VkLayerProperties> mAvailableLayers;
};

} // namespace morpheus::gfx::vulkan
