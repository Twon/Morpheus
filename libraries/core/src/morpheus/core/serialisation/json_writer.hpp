#pragma once

#include "morpheus/core/base/export.hpp"
#include "morpheus/core/base/platform.hpp"
#include "morpheus/core/serialisation/concepts/writer_archetype.hpp"

#include <rapidjson/allocators.h>
#include <rapidjson/encodings.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

namespace morpheus::serialisation
{

/// \class JsonWriter
///     Implements the concept Writer for a streaming JSON writer which writes item by item to the output stream.
class MORPHEUSCORE_EXPORT JsonWriter
{
public:
    /// \copydoc morpheus::serialisation::concepts::WriterArchetype::canBeTextual()
    static constexpr bool canBeTextual() { return true; }

    /// \copydoc morpheus::serialisation::concepts::WriterArchetype::isTextual()
    static constexpr bool isTextual() { return true; }

    /// Construct a JSON writer from an output stream.
    /// \param[in] stream The output stream to write to. This must outlive the writer as it is held by reference.
    explicit JsonWriter(std::ostream& stream);

    /// \copydoc morpheus::serialisation::concepts::WriterArchetype::beginComposite()
    void beginComposite();

    /// \copydoc morpheus::serialisation::concepts::WriterArchetype::endComposite()
    void endComposite();

    /// \copydoc morpheus::serialisation::concepts::WriterArchetype::beginValue(std::string_view const)
    void beginValue(std::string_view const key);

    /// \copydoc morpheus::serialisation::concepts::WriterArchetype::endValue()
    void endValue();

    /// \copydoc morpheus::serialisation::concepts::WriterArchetype::beginSequence(std::optional<std::size_t>)
    void beginSequence(std::optional<std::size_t> size = std::nullopt);

    /// \copydoc morpheus::serialisation::concepts::WriterArchetype::endSequence()
    void endSequence();

    /// \copydoc morpheus::serialisation::concepts::WriterArchetype::beginNullable(bool const)
    void beginNullable(bool const null);

    /// \copydoc morpheus::serialisation::concepts::WriterArchetype::endNullable()
    void endNullable();

    /// Write a boolean to the serialisation.
    void write(bool const value);
    /// Write a 8-bit unsigned integer to the serialisation.
    void write(std::uint8_t const value);
    /// Write a 8-bit integer to the serialisation.
    void write(std::int8_t const value);
    /// Write a 16-bit unsigned integer to the serialisation.
    void write(std::uint16_t const value);
    /// Write a 16-bit integer to the serialisation.
    void write(std::int16_t const value);
    /// Write a 32-bit unsigned integer to the serialisation.
    void write(std::uint32_t const value);
    /// Write a 32-bit integer to the serialisation.
    void write(std::int32_t const value);
    /// Write a 64-bit unsigned integer to the serialisation.
    void write(std::uint64_t const value);
    /// Write a 64-bit integer to the serialisation.
    void write(std::int64_t const value);
    /// Write a float to the serialisation.
    void write(float const value);
    /// Write a double to the serialisation.
    void write(double const value);
    /// \copydoc morpheus::serialisation::concepts::WriterArchetype::write(std::string_view const)
    void write(std::string_view const value);
    /// \copydoc morpheus::serialisation::concepts::WriterArchetype::write(std::span<std::byte> const)
    void write(std::span<std::byte const> const value);
    /// Write a string literal to the serialisation.
    template <std::size_t N>
    void write(const char (&str)[N])
    {
        write(std::string_view(str, N - 1));
    }

private:
    template<typename OutputStream>
    using RapidJsonWriter = rapidjson::Writer<
        OutputStream,
        rapidjson::UTF8<>,
        rapidjson::UTF8<>,
        rapidjson::CrtAllocator,
        (rapidjson::kWriteDefaultFlags | rapidjson::kWriteNanAndInfFlag)
    >;

    rapidjson::OStreamWrapper mStream;
    RapidJsonWriter<rapidjson::OStreamWrapper> mJsonWriter;
};

} // namespace morpheus::serialisation
