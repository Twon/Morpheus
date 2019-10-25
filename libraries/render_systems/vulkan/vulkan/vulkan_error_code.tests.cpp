//
//  vulkan_render_system.tests.cpp
//  MorpheusRenderSystemVulkanTest
//
//  Created by Antony Peacock on 20/10/2019.
//

#include <catch2/catch.hpp>

#include <vulkan/vulkan_error_code.hpp>


TEST_CASE("Test construction of std::error_code object via make_error_code", "[vulkan.error_code.make_error_code]")
{
    SECTION("Test success condition")
    {
        std::error_code error_code = make_error_code(VK_SUCCESS);
        REQUIRE( error_code.value() == VK_SUCCESS);
        REQUIRE( error_code.category().name() == "vulkan_error_category");
    }
    SECTION("Test success condition")
    {
        std::error_code error_code = make_error_code(VK_SUCCESS);
        REQUIRE( error_code.value() == VK_SUCCESS);
        REQUIRE( error_code.category().name() == "vulkan_error_category");
    }

    
    
    

}
