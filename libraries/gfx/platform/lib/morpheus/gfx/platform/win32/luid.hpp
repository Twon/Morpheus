#pragma once

#include <morpheus/core/base/prerequisites.hpp>
#include <morpheus/core/conformance/format.hpp>

#include <compare>

namespace morpheus::gfx::win32
{

/// \class Luid
///     Simple wrapper around the Windows LUID structure, an identifier for graphic adapters, to provide comparison operators and other utilities.
class Luid
{
public:
    Luid() = default;

    explicit Luid(LUID const& luid) noexcept
        : m_luid(luid)
    {}

    [[nodiscard]] auto get() const noexcept -> LUID const& { return m_luid; }

    [[nodiscard]] auto operator<=>(Luid const& other) const noexcept -> std::strong_ordering = default;

private:
    LUID m_luid{};
};

} // namespace morpheus::gfx::win32

/// Specialisation of the formatter for morpheus::gfx::win32::Luid to format it as a string.
template <>
struct morpheus::conf::fmt::formatter<morpheus::gfx::win32::Luid> : morpheus::conf::fmt::formatter<std::string>
{
    /// Parse the format specifier for morpheus::gfx::win32::Luid.
    /// \tparam Context The type of the format context.
    /// \param ctx The format parse context.
    /// \return An iterator to the end of the parsed format specifier.
    template <typename Context>
    constexpr auto parse(Context& context)
    {
        return std::begin(context);
    }

    /// Format the morpheus::gfx::win32::Luid as a string.
    /// \tparam Context The type of the format context.
    /// \param value The version value to format.
    /// \param context The format context.
    template <typename Context>
    constexpr auto format(morpheus::gfx::win32::Luid const& value, Context& context) const
    {
        auto const& luid = value.get();
        return morpheus::conf::fmt::format_to(context.out(), "{}:{}", luid.LowPart, value.HighPart);
    }
};
