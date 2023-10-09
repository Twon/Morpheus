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

/// \struct WriterArchtype
///     Archtype for the Writer concept, defining the minimal viable implementation.
struct WriterArchtype
{
    /// Query if the underlying serialisation format is text based.
    consteval bool isTextual() noexcept;

    /// Begin writing a composite type.
    consteval void beginComposite();

    /// End writing a composite type.
    consteval void endComposite();

    /// Begin writing a key to value type mapping.
    consteval void beginValue(std::string_view const key);

    /// End writing a key to value type mapping.
    consteval void endValue();

    /// Begin writing a sequence of values.
    /// \param[in] size Optionally provide the size of the sequence to be written.
    consteval void beginSequence(std::optional<std::size_t> size = std::nullopt);

    /// End writing a sequence of values.
    consteval void endSequence();

    /// Begin writing a nullable value.
    /// \param[in] null Will the nullable type write a value to the serialisation.
    consteval void beginNullable(bool const null);

    /// End writing a nullable value.
    consteval void endNullable();

    /// Write any arithmetic type to the serialisation.
    template <typename T> requires std::is_arithmetic_v<T>
    consteval void write(T const value);

    /// Write a string to the serialisation.
    consteval void write(std::string_view const value);

    /// Write a span of bytes to the serialisation.
    consteval void write(std::span<std::byte const> const value);
};

using WriteSerialiserArchtype = serialisation::WriteSerialiser<WriterArchtype>;

} // morpheus::serialisation::concepts
