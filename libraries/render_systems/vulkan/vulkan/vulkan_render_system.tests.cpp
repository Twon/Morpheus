//
//  vulkan_render_system.tests.cpp
//  MorpheusRenderSystemVulkanTest
//
//  Created by Antony Peacock on 20/10/2019.
//

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <vulkan/vulkan.h>


#include <iostream>
#include <vector>

TEST_CASE("Create a video mode list", "[morpheus.core.gfx.video_mode_list]")
{
    uint32_t version = 0;
    VkResult res = vkEnumerateInstanceVersion(&version);
    std::cout << "The Vulkan version is " << VK_VERSION_MAJOR(version) << "." << VK_VERSION_MINOR(version) << "." << VK_VERSION_PATCH(version);
    
    uint32_t instance_layer_count = 0;
    res = vkEnumerateInstanceLayerProperties(&instance_layer_count, nullptr);
    
    std::vector<VkLayerProperties> layers(instance_layer_count);
    res = vkEnumerateInstanceLayerProperties(&instance_layer_count, layers.data());

    std::vector<char const *> layer_names(instance_layer_count);
    std::transform(layers.begin(), layers.end(), layer_names.begin(), [](const auto& element) { return element.layerName;});

/*    for (const auto& element : layers)
    {
        res = vkEnumerateInstanceExtensionProperties(layer_name, &instance_extension_count, NULL);

    }
    layer_props.instance_extensions.resize(instance_extension_count);
    instance_extensions = layer_props.instance_extensions.data();
    res = vkEnumerateInstanceExtensionProperties(layer_name, &instance_extension_count, instance_extensions);*/
    
    char const * const app_name = "My Vulkan Test Case";
    VkApplicationInfo app_info = {};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pNext = nullptr;
    app_info.pApplicationName = app_name;
    app_info.applicationVersion = 1;
    app_info.pEngineName = app_name;
    app_info.engineVersion = 1;
    app_info.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo inst_info = {};
    inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    inst_info.pNext = nullptr;
    inst_info.flags = 0;
    inst_info.pApplicationInfo = &app_info;
    inst_info.enabledLayerCount = layer_names.size();
    inst_info.ppEnabledLayerNames = layer_names.data();
    inst_info.enabledExtensionCount = 0;//info.instance_extension_names.size();
    inst_info.ppEnabledExtensionNames =0;// info.instance_extension_names.data();

    VkInstance instance;
    res = vkCreateInstance(&inst_info, nullptr, &instance);
    if( res!= VK_SUCCESS )
        return;
    CHECK(!res);
    
    uint32_t gpu_count = 0;
    res = vkEnumeratePhysicalDevices(instance, &gpu_count, nullptr);
    
    std::vector<VkPhysicalDevice> devices(gpu_count);
    std::vector<VkPhysicalDeviceProperties> devices_properties(gpu_count);
    res = vkEnumeratePhysicalDevices(instance, &gpu_count, devices.data());
    vkGetPhysicalDeviceProperties(devices[0], &devices_properties[0]);
    
    
    INFO("The result is " << res)
    CHECK(!res);
    CHECK(gpu_count > 0);
}
