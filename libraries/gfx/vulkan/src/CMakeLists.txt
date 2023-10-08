find_package(VulkanHeaders REQUIRED)

if (NOT ${VulkanHeaders_FOUND})
    message("Vulkan not found on the system.  Unable to support Vulkan based render system.")
    return()
endif()

morpheus_add_library(
    NAME MorpheusGfxVulkan
    ALIAS morpheus::gfx::vulkan
    FOLDER "Libraries/Gfx/Vulkan"
)

target_include_directories(MorpheusGfxVulkan
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)


target_compile_definitions(MorpheusGfxVulkan
    PUBLIC
        VK_NO_PROTOTYPES
        VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1
)

target_precompile_headers(MorpheusGfxVulkan
    PRIVATE
        <vulkan/vulkan.hpp>
        <vulkan/vulkan_raii.hpp>
)

target_link_libraries(MorpheusGfxVulkan
    PUBLIC
        morpheus::gfx::platform
        Vulkan::Headers
)

set_target_properties(MorpheusGfxVulkan
    PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
)

add_subdirectory(morpheus/gfx/vulkan)
