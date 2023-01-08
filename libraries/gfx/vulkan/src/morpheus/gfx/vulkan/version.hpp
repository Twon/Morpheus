#pragma once

#include <cstdint>

namespace morpheus::gfx::vulkan
{

/// \class Version
///     Converts from a Vulkan packed version number representation to the individual components.
class Version
{
public:
    /// Constuct a Vulkan version from the packed version number:
    constexpr explicit Version(std::uint32_t const version) noexcept : mVersion(version) {}

    /// The Vulkan API variant number.
    constexpr std::uint32_t variant() const noexcept { return VK_API_VERSION_VARIANT(mVersion); }

    /// The Vulkan API major number.
    constexpr std::uint32_t major() const noexcept { return VK_API_VERSION_MAJOR(mVersion); }

    /// The Vulkan API minor number.
    constexpr std::uint32_t minor() const noexcept { return VK_API_VERSION_MINOR(mVersion); }

    /// The Vulkan API patch number.
    constexpr std::uint32_t patch() const noexcept { return VK_API_VERSION_PATCH(mVersion); }

private:
    std::uint32_t mVersion;
};

} // namespace morpheus::gfx::vulkan
