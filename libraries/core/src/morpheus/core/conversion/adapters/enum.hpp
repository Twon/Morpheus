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

template <meta::concepts::Enum E>
struct StringConverter<E>
{
    static std::string toString(E const value)
    {
        return std::string(magic_enum::enum_name(value));
    }

    static constexpr exp_ns::expected<E, std::string> fromString(std::string_view const value)
    {
        auto const enumValue = magic_enum::enum_cast<E>(value, magic_enum::case_insensitive);
        if (enumValue.has_value())
            return enumValue.value();
        else
            return exp_ns::unexpected(fmt_ns::format("Unable to convert {} to underlying enum", value));
    }
};

} // namespace morpheus::conversion
