#pragma once

#include "morpheus/core/conformance/expected.hpp"
#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conversion/string.hpp"
#include "morpheus/core/meta/concepts/enum.hpp"

#include <magic_enum/magic_enum.hpp>

#include <string>
#include <string_view>

namespace morpheus::conversion
{

/// \struct StringConverter< E >
///     A specialisation of the class template customisation point to provide conversion between enums and
///     string representations.
template <meta::concepts::Enum E>
struct StringConverter<E>
{
    /// Convert an enum value to its string representation.
    /// \param value The enum value to convert.
    /// \return A string representation of the enum value.
    /// \note The string representation is the name of the enum value as defined in the enum declaration.
    static std::string toString(E const value) { return std::string(magic_enum::enum_name(value)); }

    /// Convert a string representation to an enum value.
    /// \param value The string representation to convert.
    /// \return An expected containing the enum value if the conversion was successful, or an unexpected error if it failed.
    static constexpr conf::exp::expected<E, std::string> fromString(std::string_view const value)
    {
        auto const enumValue = magic_enum::enum_cast<E>(value, magic_enum::case_insensitive);
        if (enumValue.has_value())
            return enumValue.value();
        else
            return conf::exp::unexpected(conf::fmt::format("Unable to convert {} to underlying enum", value));
    }
};

} // namespace morpheus::conversion
