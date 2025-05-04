#pragma once

#include <morpheus/core/conformance/format.hpp>
#include <morpheus/core/conformance/scan.hpp>

#include <cstdint>

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

template <>
struct morpheus::scan_ns::scanner<morpheus::application::Version> : morpheus::scan_ns::scanner<std::string>
{
    template <typename Context>
    auto scan(morpheus::application::Version& val, Context& ctx) const -> morpheus::scan_ns::scan_expected<typename Context::iterator>
    {
        return morpheus::scan_ns::scan<std::uint16_t, std::uint16_t, std::uint16_t>(ctx.range(), "{{major={},minor={},patch={}}}")
            .transform(
                [&val](auto const& result)
                {
                    std::tie(val.major, val.minor, val.patch) = result.values();
                    return result.begin();
                });
    }
};

