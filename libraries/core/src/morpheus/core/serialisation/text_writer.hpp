#pragma once

#include <cstdint>
#include <ostream>

namespace morpheus::serialisation
{

class TextWriter 
{
public:
    static constexpr bool canBeTextual() { return true; }

    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::isTextual()
    static constexpr bool isTextual() { return true; }

    explicit TextWriter(std::ostream& stream) noexcept : mStream(stream) {}

    /// \copydoc morpheus::serialisation::JsonWriter::write(bool)
    void write(bool value) {}
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::uint8_t)
    void write(std::uint8_t value) {}
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::int8_t)
    void write(std::int8_t value) {}
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::uint16_t)
    void write(std::uint16_t value) {}
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::int16_t)
    void write(std::int16_t value) {}
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::uint32_t)
    void write(std::uint32_t value) {}
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::int32_t)
    void write(std::int32_t value) {}
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::uint64_t)
    void write(std::uint64_t value) {}
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::int64_t)
    void write(std::int64_t value) {}
    /// \copydoc morpheus::serialisation::JsonWriter::write(float)
    void write(float value) {}
    /// \copydoc morpheus::serialisation::JsonWriter::write(double)
    void write(double value) {}

    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::write(std::string_view const)
    void write(std::string_view const value) {}
    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::write(std::span<std::byte> const)
    void write(std::span<std::bytes> const value) {}

private:
    std::ostream& mStream;
};

}