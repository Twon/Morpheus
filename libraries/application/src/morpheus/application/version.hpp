#pragma once

#include <morpheus/core/conformance/format.hpp>

namespace morpheus::application
{

/// \class Version
///     Simple type representing semantic versioning: https://semver.org/
struct Version
{
    std::uint16_t major = 0; ///< Major component of the version.
    std::uint16_t minor = 0; ///< Minor component of the version.
    std::uint16_t patch = 0; ///< Patch component of the version.
};

} // namespace morpheus::application

template <>
struct morpheus::fmt_ns::formatter<morpheus::application::Version>
{
    template <typename Context>
    constexpr auto parse(Context& context)
    {
        return std::begin(context);
    }

    template <typename Context>
    constexpr auto format(morpheus::application::Version const& value, Context& context) const
    {
        return morpheus::fmt_ns::format_to(context.out(), "{{major={},minor={},patch={}}}", value.major, value.minor, value.patch);
    }
};
