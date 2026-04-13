#pragma once

#include "morpheus/core/serialisation/read_serialiser_decl.hpp"

#include <cstddef>
#include <cstdint>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <type_traits>

namespace morpheus::serialisation::concepts
{

/// \struct ReaderArchetype
///     Archetype for the Reader concept, defining the minimal viable implementation.
struct ReaderArchetype
{
    /// Query if the underlying serialisation format is text based.
    consteval bool isTextual() noexcept;

    /// Begin reading a composite type.
    consteval void beginComposite();

    /// End reading a composite type.
    consteval void endComposite();

    /// Begin reading a key to value type mapping.
    consteval void beginValue(std::string_view const key);

    /// End reading a key to value type mapping.
    consteval void endValue();

    /// Begin reading a sequence of values.
    /// \return Optionally provide the size of the sequence to be written.
    consteval std::optional<std::size_t> beginSequence();

    /// End reading a sequence of values.
    consteval void endSequence();

    /// Begin reading a nullable value.
    /// \return If the nullable type should read a value from the serialisation.
    consteval bool beginNullable();

    /// End reading a nullable value.
    consteval void endNullable();

    // Work around for Doxygen duplicate symbols bug, this is now fixed in Doyxgn 1.14.0:
    // https://github.com/doxygen/doxygen/commit/64d0cb7f695b2ebe63131c06b7762c1f75212c28
    /// Read any arithmetic type from the serialisation.
    template <typename T>
    requires std::is_arithmetic_v<T>
    consteval T read();

    /// Read a string from the serialisation.
    template <typename T>
    requires std::is_same_v<T, std::string>
    consteval T read();

    /// Read a blob of binary from the serialisation.
    template <typename T>
    requires std::is_same_v<T, std::vector<std::byte>>
    consteval T read();
};

using ReadSerialiserArchetype = serialisation::ReadSerialiser<ReaderArchetype>;

} // namespace morpheus::serialisation::concepts
