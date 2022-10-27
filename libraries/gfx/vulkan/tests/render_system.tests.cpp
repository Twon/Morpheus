
#include <catch2/catch_all.hpp>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>

#include <iostream>
#include <vector>

TEST_CASE("Create a video mode list", "[morpheus.core.gfx.video_mode_list]")
{
/*    uint32_t version = 0;
    VkResult res = vkEnumerateInstanceVersion(&version);
    INFO("The Vulkan version is " << VK_VERSION_MAJOR(version) <<"."<< VK_VERSION_MINOR(version) <<"."<< VK_VERSION_PATCH(version));
    
    uint32_t instance_layer_count = 0;
    res = vkEnumerateInstanceLayerProperties(&instance_layer_count, nullptr);
    
    INFO("Found " << instance_layer_count << " layers in Vulkan instance.");
    std::vector<VkLayerProperties> layers(instance_layer_count);
    res = vkEnumerateInstanceLayerProperties(&instance_layer_count, layers.data());

    std::vector<char const *> layer_names(instance_layer_count);
    std::transform(layers.begin(), layers.end(), layer_names.begin(), [](const auto& element) { return element.layerName;});
    std::for_each(layers.begin(), layers.end(),  [](const auto& element) { INFO("Layer: " << element.layerName);});
*/
//    for (const auto& element : layers)
//    {
//        res = vkEnumerateInstanceExtensionProperties(layer_name, &instance_extension_count, NULL);
//
//    }
//    layer_props.instance_extensions.resize(instance_extension_count);
//    instance_extensions = layer_props.instance_extensions.data();
//    res = vkEnumerateInstanceExtensionProperties(layer_name, &instance_extension_count, instance_extensions);
    CHECK(true);
    char const * const appName = "My Vulkan Test Case";
    char const * const engineName = "My Vulkan Test Case Engine";
    vk::raii::Context context;
    vk::ApplicationInfo applicationInfo(appName, 1, engineName, 1, VK_API_VERSION_1_1);
    vk::InstanceCreateInfo instanceCreateInfo({}, &applicationInfo);
    vk::raii::Instance instance(context, instanceCreateInfo);
    auto const physicalDevices = instance.enumeratePhysicalDevices();
    WARN("The num physical devices is " << physicalDevices.size());
    for (auto const& device : physicalDevices)
    {
        auto const& props = device.getProperties();
        WARN("Devices apiVersion is " << props.apiVersion);
        WARN("Devices driverVersion is " << props.driverVersion);
        WARN("Devices vendorId is " << props.vendorID);
        CHECK(true);
        //    auto const displayProperties = device.getDisplayPropertiesKHR();
        //    INFO("The num physical devices displays is " << displayProperties.size());

    }
//    std::vector<VkPhysicalDeviceProperties> devices_properties(gpu_count);
//    res = vkEnumeratePhysicalDevices(instance, &gpu_count, devices.data());
//    vkGetPhysicalDeviceProperties(devices[0], &devices_properties[0]);
    
    
//    INFO("The result is " << res)
//    CHECK(!res);
//    CHECK(gpu_count > 0);
}
