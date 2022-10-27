#include "morpheus/gfx/vulkan/error_codes.hpp"

#include <catch2/catch_all.hpp>
#include <string_view>
#include <array>

TEST_CASE("Test construction of std::error_code object via make_error_code", "[vulkan.error_code.make_error_code]")
{
    constexpr std::array<VkResult, 32> vkUniqueResults =
    {
        VK_SUCCESS,
        VK_NOT_READY,
        VK_TIMEOUT,
        VK_EVENT_SET,
        VK_EVENT_RESET,
        VK_INCOMPLETE,
        VK_ERROR_OUT_OF_HOST_MEMORY,
        VK_ERROR_OUT_OF_DEVICE_MEMORY,
        VK_ERROR_INITIALIZATION_FAILED,
        VK_ERROR_DEVICE_LOST,
        VK_ERROR_MEMORY_MAP_FAILED,
        VK_ERROR_LAYER_NOT_PRESENT,
        VK_ERROR_EXTENSION_NOT_PRESENT,
        VK_ERROR_FEATURE_NOT_PRESENT,
        VK_ERROR_INCOMPATIBLE_DRIVER,
        VK_ERROR_TOO_MANY_OBJECTS,
        VK_ERROR_FORMAT_NOT_SUPPORTED,
        VK_ERROR_FRAGMENTED_POOL,
        VK_ERROR_OUT_OF_POOL_MEMORY,
        VK_ERROR_INVALID_EXTERNAL_HANDLE,
        VK_ERROR_SURFACE_LOST_KHR,
        VK_ERROR_NATIVE_WINDOW_IN_USE_KHR ,
        VK_SUBOPTIMAL_KHR,
        VK_ERROR_OUT_OF_DATE_KHR,
        VK_ERROR_INCOMPATIBLE_DISPLAY_KHR,
        VK_ERROR_VALIDATION_FAILED_EXT,
        VK_ERROR_INVALID_SHADER_NV,
        VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT,
        VK_ERROR_FRAGMENTATION_EXT,
        VK_ERROR_NOT_PERMITTED_EXT,
        VK_ERROR_INVALID_DEVICE_ADDRESS_EXT,
        VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT,
    };
    for (const auto result_code : vkUniqueResults)
    {
        std::error_code error_code = make_error_code(result_code);
        INFO("Testing VkResult enum: " << error_code);
        REQUIRE( error_code.value() == result_code);
        REQUIRE( std::string_view(error_code.category().name()) == std::string_view("vulkan_error_category"));
        REQUIRE( error_code.message() != "unknown" );
    }
}
