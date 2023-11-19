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

RenderSystem::RenderSystem(std::string_view const appName, std::string_view const engineName)
: mInstance( // LCOV_EXCL_LINE
      [&]    // LCOV_EXCL_LINE
      {
          // initialize the vk::ApplicationInfo structure
          vk::ApplicationInfo applicationInfo(appName.data(), 1, engineName.data(), 1, VK_API_VERSION_1_1); // LCOV_EXCL_LINE

          // initialize the vk::InstanceCreateInfo
          vk::InstanceCreateInfo instanceCreateInfo({}, &applicationInfo); // LCOV_EXCL_LINE

          // create an Instance
          return vk::raii::Instance(mContext, instanceCreateInfo); // LCOV_EXCL_LINE
      }())
, mVulkanVersion(mContext.enumerateInstanceVersion())                   // LCOV_EXCL_LINE
, mAvailableExtensions(mContext.enumerateInstanceExtensionProperties()) // LCOV_EXCL_LINE
, mAvailableLayers(mContext.enumerateInstanceLayerProperties())         // LCOV_EXCL_LINE
, mAdapters(enumerateAdapters(mInstance))                               // LCOV_EXCL_LINE
{
}

//---------------------------------------------------------------------------------------------------------------------

RenderSystem::~RenderSystem()
{

}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx::vulkan
