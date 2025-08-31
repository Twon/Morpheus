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

/// Specialisation of the formatter for morpheus::application::Version to format it as a string.
template <>
struct morpheus::conf::fmt::formatter<morpheus::application::Version> : morpheus::conf::fmt::formatter<std::string>
{
    /// Parse the format specifier for morpheus::application::Version.
    /// \tparam Context The type of the format context.
    /// \param ctx The format parse context.
    /// \return An iterator to the end of the parsed format specifier.
    template <typename Context>
    constexpr auto parse(Context& context)
    {
        return std::begin(context);
    }

    /// Format the morpheus::application::Version as a string.
    /// \tparam Context The type of the format context.
    /// \param value The version value to format.
    /// \param context The format context.
    template <typename Context>
    constexpr auto format(morpheus::application::Version const& value, Context& context) const
    {
        return morpheus::conf::fmt::format_to(context.out(), "{{major={},minor={},patch={}}}", value.major, value.minor, value.patch);
    }
};

/// Specialisation of the scanner for morpheus::application::Version to scan it from a string.
template <>
struct morpheus::conf::scan::scanner<morpheus::application::Version> : morpheus::conf::scan::scanner<std::string>
{
    /// Scan for the version.
    /// \tparam Context The type of the format context.
    /// \param val The version value to populate.
    /// \param ctx The scan context.
    /// \return An expected iterator pointing to the end of the scanned version, or the scan error if it failed.
    template <typename Context>
    auto scan(morpheus::application::Version& val, Context& ctx) const -> morpheus::conf::scan::scan_expected<typename Context::iterator>
    {
        return morpheus::conf::scan::scan<std::uint16_t, std::uint16_t, std::uint16_t>(ctx.range(), "{{major={},minor={},patch={}}}")
            .transform(
                [&val](auto const& result)
                {
                    std::tie(val.major, val.minor, val.patch) = result.values();
                    return result.begin();
                });
    }
};
