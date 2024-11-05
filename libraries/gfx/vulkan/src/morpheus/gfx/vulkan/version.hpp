#pragma once

#include <morpheus/core/conformance/format.hpp>

#include <vulkan/vulkan.hpp>
#include <cstdint>

namespace morpheus::gfx::vulkan
{

/// \class Version
///     Converts from a Vulkan packed version number representation to the individual components.
class Version
{
public:
    /// Construct a Vulkan version from the packed version number:
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


template <>
struct morpheus::fmt_ns::formatter<morpheus::gfx::vulkan::Version>
{
    template <typename Context>
    constexpr auto parse(Context& context)
    {
        return std::begin(context);
    }

    template <typename Context>
    constexpr auto format(morpheus::gfx::vulkan::Version const& value, Context& context) const
    {
        return morpheus::fmt_ns::format_to(context.out(), "{{variant={},major={},minor={},patch={}}}", value.variant(), value.major(), value.minor(),
                                           value.patch());
    }
};
