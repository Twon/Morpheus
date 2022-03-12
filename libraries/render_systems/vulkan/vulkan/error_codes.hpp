#pragma once

#include <vulkan/vulkan.hpp>
#include <system_error>

namespace std
{
    template <> struct is_error_code_enum<VkResult> : true_type {};
}

namespace morpheus::gfx::vulkan
{

namespace details
{
    class vulkan_error_category;
}

/// Retrieve the one instance of the Vulkan error category
/// \return The one instance of the Vulkan error category.
const details::vulkan_error_category& vulkan_error_category() noexcept;

} // namespace morpheus::gfx::vulkan

/// Overload the global make_error_code() free function with VkResult enum. It will be found via ADL by the compiler if needed.
/// \param[in] error The error raised by the underlying Vulkan API.
/// \return A std::error_code with Vulkan error encoded into it.
std::error_code make_error_code(VkResult error);
