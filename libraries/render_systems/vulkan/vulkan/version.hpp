#pragma once

#include <cstdint>

namespace morpheus::gfx::vulkan
{

class Version
{
public:
    explicit Version(std::uint32_t const version) : mVersion(version) {}

    constexpr std::uint32_t variant() const { return VK_API_VERSION_VARIANT(mVersion); }
    constexpr std::uint32_t major() const { return VK_API_VERSION_MAJOR(mVersion); }
    constexpr std::uint32_t minor() const { return VK_API_VERSION_MINOR(mVersion); }
    constexpr std::uint32_t patch() const { return VK_API_VERSION_PATCH(mVersion); }

private:
    std::uint32_t mVersion;
};

} // namespace morpheus::gfx::vulkan
