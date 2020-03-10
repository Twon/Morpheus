#include <catch2/catch.hpp>
#include "vulkan_instance.hpp"
#include <string_view>

using namespace morpheus::gfx::vulkan::primitives;

TEST_CASE("Walk a Vulkan instance application info entity through its Life-cycle", "[morpheus.gfx.vulkan.instance.application_info]")
{
    GIVEN("A default constructed application_info instance")//The ability to track internal copies and deletes of the default constructor")
    {
        const std::string application_name = "Test application";
        instance::application_info info(application_name );

        WHEN("Default-constructed")
        {
            const auto& vulkan_primitive = static_cast<const VkApplicationInfo&>(info);

            THEN("Ensure no copies or deletes occur")
            {
                REQUIRE(vulkan_primitive.sType == VK_STRUCTURE_TYPE_APPLICATION_INFO);
                REQUIRE(vulkan_primitive.pNext == nullptr);
                REQUIRE(vulkan_primitive.pApplicationName != nullptr);
                REQUIRE(std::string_view(vulkan_primitive.pApplicationName) == application_name);
                REQUIRE(vulkan_primitive.applicationVersion == 1);
                REQUIRE(vulkan_primitive.pEngineName != nullptr);
                REQUIRE(std::string_view(vulkan_primitive.pEngineName) == application_name);
                REQUIRE(vulkan_primitive.engineVersion == 1);
                REQUIRE(vulkan_primitive.apiVersion == get_highest_supported_instance_version());
            }
        }
    }
}

TEST_CASE("Walk a Vulkan instance create info entity through its Life-cycle", "[morpheus.gfx.vulkan.instance.create_info]")
{
    GIVEN("A default constructed create_info instance")
    {
        instance::create_info info;

        WHEN("Default-constructed")
        {
            const auto& vulkan_primitive = static_cast<const VkInstanceCreateInfo&>(info);

            THEN("Ensure no copies or deletes occur")
            {
                REQUIRE(vulkan_primitive.sType == VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO);
                REQUIRE(vulkan_primitive.pNext == nullptr);
                REQUIRE(vulkan_primitive.flags == 0);
                REQUIRE(vulkan_primitive.pApplicationInfo == nullptr);
                REQUIRE(vulkan_primitive.enabledLayerCount == 0);
                REQUIRE(vulkan_primitive.ppEnabledLayerNames == nullptr);
                REQUIRE(vulkan_primitive.enabledExtensionCount == 0);
                REQUIRE(vulkan_primitive.ppEnabledExtensionNames == nullptr);
            }
        }
    }
}


TEST_CASE("Walk a Vulkan instance through its Life-cycle", "[morpheus.gfx.vulkan.instance]")
{

}
