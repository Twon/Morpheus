#include <morpheus/gfx/vulkan/error_codes.hpp>


namespace morpheus::gfx::vulkan
{

namespace details
{
/*! \class vulkan_error_category
        Defines an error code category for Vulkan return codes to plug them into the std::error_code framework.
 */
class vulkan_error_category : public std::error_category {
public:
    /*! Queries a short form descriptive name for the category.
        \return Short form name of the category.
     */
    const char* name() const noexcept override final { return "vulkan_error_category"; }

    /*! Queries an error string describing the error.
        \return The error message.
     */
    std::string message(int c) const override final
    {
        switch (static_cast<VkResult>(c))
        {
        case VK_SUCCESS:
            return "Command successfully completed.";
        case VK_NOT_READY:
            return "A fence or query has not yet completed.";
        case VK_TIMEOUT:
            return "A wait operation has not completed in the specified time.";
        case VK_EVENT_SET:
            return "An event is signaled.";
        case VK_EVENT_RESET:
            return "An event is unsignaled.";
        case VK_INCOMPLETE:
            return "A return array was too small for the result.";
        case VK_SUBOPTIMAL_KHR:
            return " swapchain no longer matches the surface properties exactly, but can still be used to present to the surface successfully.";
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            return "A host memory allocation has failed.";
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            return "A device memory allocation has failed.";
        case VK_ERROR_INITIALIZATION_FAILED:
            return "Initialization of an object could not be completed for implementation-specific reasons.";
        case VK_ERROR_DEVICE_LOST:
            return "The logical or physical device has been lost.";
        case VK_ERROR_MEMORY_MAP_FAILED:
            return "Mapping of a memory object has failed.";
        case VK_ERROR_LAYER_NOT_PRESENT:
            return "A requested layer is not present or could not be loaded.";
        case VK_ERROR_EXTENSION_NOT_PRESENT:
            return "A requested extension is not supported..";
        case VK_ERROR_FEATURE_NOT_PRESENT:
            return "A requested feature is not supported.";
        case VK_ERROR_INCOMPATIBLE_DRIVER:
            return "The requested version of Vulkan is not supported by the driver or is otherwise incompatible for implementation-specific reasons.";
        case VK_ERROR_TOO_MANY_OBJECTS:
            return "Too many objects of the type have already been created.";
        case VK_ERROR_FORMAT_NOT_SUPPORTED:
            return "A requested format is not supported on this device.";
        case VK_ERROR_FRAGMENTED_POOL:
            return "A requested pool allocation has failed due to fragmentation of the pool’s memory.";
        case VK_ERROR_SURFACE_LOST_KHR:
            return "A surface is no longer available.";
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
            return "The requested window is already in use by Vulkan or another API in a manner which prevents it from being used again.";
        case VK_ERROR_OUT_OF_DATE_KHR:
            return "A surface has changed in such a way that it is no longer compatible with the swapchain, and further presentation requests using the swapchain will fail. Applications must query the new surface properties and recreate their swapchain if they wish to continue presenting to the surface.";
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
            return "The display used by a swapchain does not use the same presentable image layout, or is incompatible in a way that prevents sharing an image";
        case VK_ERROR_VALIDATION_FAILED_EXT:
            return "The primary expected use of VK_ERROR_VALIDATION_FAILED_EXT is for validation layer testing. It's not expected that an application would see this this error code during normal use of the validation layers.";
        case VK_ERROR_INVALID_SHADER_NV:
            return "One or more shaders failed to compile or link. More details are reported back to the application via VK_EXT_debug_report if enabled.";
        case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
            return "When creating an image with VkImageDrmFormatModifierExplicitCreateInfoEXT, it is the application’s responsibility to satisfy all valid usage requirements. However, the implementation must validate that the provided pPlaneLayouts, when combined with the provided drmFormatModifier and other creation parameters in VkImageCreateInfo and its pNext chain, produce a valid image.";
        case VK_ERROR_OUT_OF_POOL_MEMORY:
            return "A pool memory allocation has failed. This must only be returned if no attempt to allocate host or device memory was made to accommodate the new allocation. If the failure was definitely due to fragmentation of the pool, VK_ERROR_FRAGMENTED_POOL should be returned instead.";
        case VK_ERROR_INVALID_EXTERNAL_HANDLE:
            return "An external handle is not a valid handle of the specified type.";
        case VK_ERROR_FRAGMENTATION_EXT:
            return "A descriptor pool creation has failed due to fragmentation.";
        case VK_ERROR_NOT_PERMITTED_EXT:
            return "the driver implementation may deny requests to acquire a priority above the default priority (VK_QUEUE_GLOBAL_PRIORITY_MEDIUM_EXT) if the caller does not have sufficient privileges. In this scenario VK_ERROR_NOT_PERMITTED_EXT is returned.";
        case VK_ERROR_INVALID_DEVICE_ADDRESS_EXT:
            return "A buffer creation failed because the requested address is not available.";
        case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
            return "An operation on a swapchain created with VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT failed as it did not have exlusive full-screen access. This may occur due to implementation-dependent reasons, outside of the application’s control.";
        default:
            return "unknown";
      }
    }

    static const vulkan_error_category& getSingleInstance() noexcept { return mSingleInstance; }
private:
    static vulkan_error_category mSingleInstance;
};

vulkan_error_category vulkan_error_category::mSingleInstance;

} // namespace morpheus::gfx::vulkan::details

const details::vulkan_error_category& vulkan_error_category() noexcept
{
    return details::vulkan_error_category::getSingleInstance();
}

} // namespace morpheus::gfx::vulkan

std::error_code make_error_code(VkResult error)
{
    return {static_cast<int>(error), morpheus::gfx::vulkan::vulkan_error_category()};
}
