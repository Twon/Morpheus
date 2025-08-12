#include "morpheus/gfx/vulkan/render_system.hpp"
#include <vulkan/vulkan.h>

VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

namespace morpheus::gfx::vulkan
{

namespace
{

/*auto get_physical_devices()
{
//    uint32_t deviceCount = 0;
//    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
}*/
}

//---------------------------------------------------------------------------------------------------------------------
// LCOV_EXCL_START
RenderSystem::RenderSystem(std::string_view const appName, std::string_view const engineName)
    : mInstance(
          [&]
          {
              // initialize the vk::ApplicationInfo structure
              vk::ApplicationInfo applicationInfo(appName.data(), 1, engineName.data(), 1, VK_API_VERSION_1_1);

              // initialize the vk::InstanceCreateInfo
              vk::InstanceCreateInfo instanceCreateInfo({}, &applicationInfo);

              // create an Instance
              return vk::raii::Instance(mContext, instanceCreateInfo);
          }())
    , mVulkanVersion(mContext.enumerateInstanceVersion())
    , mAvailableExtensions(mContext.enumerateInstanceExtensionProperties())
    , mAvailableLayers(mContext.enumerateInstanceLayerProperties())
    , mAdapters(enumerateAdapters(mInstance))
{}
// LCOV_EXCL_STOP
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx::vulkan
