#include "vulkan_instance.hpp"
#include <utility>

namespace morpheus::gfx::vulkan::primitives
{
    uint32_t get_highest_supported_instance_version()
    {
        uint32_t version = VK_API_VERSION_1_0;

        const auto instance_version_func = vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion");
        if (instance_version_func)
        {
            using vkEnumerateInstanceVersion_func = VkResult (*)(uint32_t* );
            const auto enum_version_func = reinterpret_cast<vkEnumerateInstanceVersion_func>(instance_version_func);
            enum_version_func(&version);
        }
        return version;
    }

/*
    typedef struct VkApplicationInfo {
        VkStructureType    sType;
        const void*        pNext;
        const char*        pApplicationName;
        uint32_t           applicationVersion;
        const char*        pEngineName;
        uint32_t           engineVersion;
        uint32_t           apiVersion;
    } VkApplicationInfo;
*/

    instance::application_info::application_info(std::string name) noexcept
    :   mName(std::move(name)),
        mInfo{ VK_STRUCTURE_TYPE_APPLICATION_INFO, nullptr, mName.c_str(), 1, mName.c_str(), 1, get_highest_supported_instance_version()}
    {
    }

    /*

 typedef struct VkInstanceCreateInfo {
    VkStructureType             sType;
    const void*                 pNext;
    VkInstanceCreateFlags       flags;
    const VkApplicationInfo*    pApplicationInfo;
    uint32_t                    enabledLayerCount;
    const char* const*          ppEnabledLayerNames;
    uint32_t                    enabledExtensionCount;
    const char* const*          ppEnabledExtensionNames;
} VkInstanceCreateInfo;

     */

    instance::create_info::create_info() noexcept
    :    mInfo{ VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, nullptr, 0,
                nullptr, 0, nullptr, 0, nullptr }
    {
    }

} // namespace morpheus::gfx::vulkan
