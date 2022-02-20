#include "vulkan_instance.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <tuple>

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
//        return std::make_tuple(VK_VERSION_MAJOR(version), VK_VERSION_MINOR(version), VK_VERSION_PATCH(version));
    }

    std::vector<VkLayerProperties> enumerate_instance_layer_properties()
    {
        VkResult res = VK_SUCCESS;
        uint32_t instance_layer_count = 0;
        std::vector<VkLayerProperties> layers;
        do{
            res = vkEnumerateInstanceLayerProperties(&instance_layer_count, nullptr);
            if (res == VK_SUCCESS && instance_layer_count)
            {
                layers.resize(instance_layer_count);
                res = vkEnumerateInstanceLayerProperties(&instance_layer_count, layers.data());
            }
        }
        while(res == VK_INCOMPLETE);
        return layers;
    }


    std::vector<VkExtensionProperties> enumerate_instance_extension_properties(const std::optional<std::string>& layer)
    {
        VkResult res = VK_SUCCESS;
        uint32_t instance_extensions_count = 0;
        std::vector<VkExtensionProperties> extensions;
        do{
            res = vkEnumerateInstanceExtensionProperties((layer) ? layer.value().c_str() : nullptr, &instance_extensions_count, nullptr);
            if (res == VK_SUCCESS && instance_extensions_count)
            {
                extensions.resize(instance_extensions_count);
                res = vkEnumerateInstanceExtensionProperties((layer) ? layer.value().c_str() : nullptr, &instance_extensions_count, extensions.data());
            }
        }
        while(res == VK_INCOMPLETE);
        return extensions;
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
        mInfo{ VK_STRUCTURE_TYPE_APPLICATION_INFO, nullptr, mName.c_str(), VK_MAKE_VERSION(1, 0, 0), mName.c_str(), VK_MAKE_VERSION(1, 0, 0), get_highest_supported_instance_version()}
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

    instance::create_info::create_info(
        const std::optional<std::vector<VkLayerProperties>>& layers
    ) noexcept
    :    mInfo{ VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, nullptr, 0,
                nullptr, 0, nullptr, 0, nullptr }
    {
        if (layers)
        {
            mLayerNames.resize(layers.value().size());
            std::transform(layers.value().begin(), layers.value().end(), mLayerNames.begin(), [](const auto& element) { return element.layerName;});
            mInfo.enabledLayerCount = mLayerNames.size();
            mInfo.ppEnabledLayerNames = mLayerNames.data();
        }
    }

    instance::create_info::create_info(
        const application_info& app_info,
        const std::optional<std::vector<VkLayerProperties>>& layers
    ) noexcept
    :    mInfo{ VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, nullptr, 0,
                &app_info, 0, nullptr, 0, nullptr }
    {
        if (layers)
        {
            mLayerNames.resize(layers.value().size());
            std::transform(layers.value().begin(), layers.value().end(), mLayerNames.begin(), [](const auto& element) { return element.layerName;});
            mInfo.enabledLayerCount = mLayerNames.size();
            mInfo.ppEnabledLayerNames = mLayerNames.data();
        }
    }

    instance::instance(const create_info& info)
    {
        if (vkCreateInstance(&info, nullptr, &mInstance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
    }

    instance::~instance()
    {
        vkDestroyInstance(mInstance, nullptr);
    }

} // namespace morpheus::gfx::vulkan
