#pragma once

#include <morpheus/core/conformance/format.hpp>

namespace morpheus::application
{

/// \class Version
///     Simple type representing semantic versioning: https://semver.org/
struct Version
{
    std::uint16_t max = 0;
    std::uint16_t min = 0;
    std::uint16_t patch = 0;
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
        return morpheus::fmt_ns::format_to(context.out(), "{{max={},min={},patch={}}}", value.max, value.min, value.patch);
    }
};
