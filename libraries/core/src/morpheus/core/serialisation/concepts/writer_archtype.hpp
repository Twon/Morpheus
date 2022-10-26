#pragma once

#include "morpheus/core/serialisation/write_serialiser_decl.hpp"

#include <cstddef>
#include <cstdint>
#include <concepts>
#include <optional>
#include <span>
#include <string_view>
#include <type_traits>

namespace morpheus::serialisation::concepts
{

struct WriterArchtype
{
    consteval bool isTextual() noexcept;

    consteval void beginComposite();
    consteval void endComposite();
    consteval void beginValue(std::string_view const key);
    consteval void endValue();
    consteval void beginSequence(std::optional<std::size_t> = std::nullopt);
    consteval void endSequence();
    consteval void beginNullable(bool const null);
    consteval void endNullable();

    template <typename T> requires std::is_arithmetic_v<T>
    consteval void write(T const value);

    consteval void write(std::string_view const value);
    consteval void write(std::span<std::byte> const value);
};

using WriteSerialiserArchtype = serialisation::WriteSerialiser<WriterArchtype>;

} // morpheus::serialisation::concepts