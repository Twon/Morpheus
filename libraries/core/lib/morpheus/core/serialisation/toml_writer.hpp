#pragma once

#include "morpheus/core/serialisation/concepts/writer_archetype.hpp"

#include <toml++/toml.hpp>

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

namespace morpheus::serialisation
{

class TomlWriter
{
public:
    /// \copydoc morpheus::serialisation::concepts::WriterArchetype::isTextual()
    static constexpr bool isTextual() { return true; }

    /// Construct a TOML writer from an output stream.
    /// \param[in] stream The output stream to write to.  This must outlive the writer as its held by reference.
    explicit TomlWriter(std::ostream& stream);

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

    /// \copydoc morpheus::serialisation::JsonWriter::write(bool)
    void write(bool value);
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::byte)
    void write(std::byte value);
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::uint8_t)
    void write(std::uint8_t value);
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::int8_t)
    void write(std::int8_t value);
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::uint16_t)
    void write(std::uint16_t value);
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::int16_t)
    void write(std::int16_t value);
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::uint32_t)
    void write(std::uint32_t value);
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::int32_t)
    void write(std::int32_t value);
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::uint64_t)
    void write(std::uint64_t value);
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::int64_t)
    void write(std::int64_t value);
    /// \copydoc morpheus::serialisation::JsonWriter::write(float)
    void write(float value);
    /// \copydoc morpheus::serialisation::JsonWriter::write(double)
    void write(double value);
    /// \copydoc morpheus::serialisation::concepts::WriterArchetype::write(std::string_view const)
    void write(std::string_view value);
    /// \copydoc morpheus::serialisation::concepts::WriterArchetype::write(std::span<std::byte> const)
    void write(std::span<std::byte const> const value);

private:
    std::ostream& mStream;
};

} // namespace morpheus::serialisation
