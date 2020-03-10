#include <vulkan/vulkan_render_system.hpp>


namespace morpheus::gfx::vulkan
{

namespace
{

const auto get_vulkan_version()
{
    uint32_t version = 0;
    vkEnumerateInstanceVersion(&version);
    return std::tuple(VK_VERSION_MAJOR(version), VK_VERSION_MINOR(version),  VK_VERSION_PATCH(version));
}

const auto get_instance_layer_properties()
{
    uint32_t instance_layer_count = 0;
    VkResult res = vkEnumerateInstanceLayerProperties(&instance_layer_count, nullptr);
    std::vector<VkLayerProperties> layers(instance_layer_count);
    res = vkEnumerateInstanceLayerProperties(&instance_layer_count, layers.data());
    return layers;
}

const auto get_instance_extension_properties()
{
    uint32_t instance_extension_count = 0;
    VkResult res = vkEnumerateInstanceExtensionProperties(nullptr, &instance_extension_count, nullptr);
    std::vector<VkExtensionProperties> extensions(instance_extension_count);
    res = vkEnumerateInstanceExtensionProperties(nullptr, &instance_extension_count, extensions.data());
    return extensions;
}

const auto get_physical_devices()
{
//    uint32_t deviceCount = 0;
//    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
}

}

//---------------------------------------------------------------------------------------------------------------------

render_system::render_system()
:   mVulkanVersion(get_vulkan_version()),
    mAvailableLayers(get_instance_layer_properties())
{

}

//---------------------------------------------------------------------------------------------------------------------

render_system::~render_system()
{

}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx::vulkan
