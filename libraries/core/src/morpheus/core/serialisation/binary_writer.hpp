#pragma once

#include "morpheus/core/base/cold.hpp"
#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/serialisation/exceptions.hpp"

#include <cstdint>
#include <cstddef>
#include <iosfwd>
#include <optional>
#include <span>
#include <string_view>

namespace morpheus::serialisation
{

/// \class BinaryWriter
///     A serialisation writer that serialises to a binary stream but support all underlying
///     out stream types which allows output to many sources including:
///         - Binary to block of memory.
///         - Binary to a file.
///         - Binary to memory mapped file.
///         - Binary to pipe.
class BinaryWriter
{
public:
    BinaryWriter(std::ostream& outStream)
    : mOutStream(outStream)
    {
    }

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::isTextual()
    static constexpr bool isTextual() { return false; }

    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::beginComposite()
    void beginComposite() {}

    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::endComposite()
    void endComposite() {}

    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::beginValue()
    void beginValue(std::string_view const key) {}

    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::endValue()
    void endValue() {}

    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::beginSequence()
    void beginSequence(std::optional<std::size_t> size = std::nullopt)
    {
        if (size)
            write(size.value());
        else
            throwBinaryException("Sequence does not provide size.  This must be proided for binary serialisation.");
    }

    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::endSequence()
    void endSequence() {}

    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::beginNullable()
    void beginNullable(bool const null)
    {
        write(null);
    }

    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::endNullable()
    void endNullable() {}

    template <typename T>
    requires std::integral<T> or std::floating_point<T>
    void write(T const value)
    {
        auto const writtenSize = mOutStream.rdbuf()->sputn(reinterpret_cast<const char*>(&value), sizeof(value));
        if (writtenSize != sizeof(value))
            throwBinaryException(fmt_ns::format("Error writing data to stream.  Attempted to write {} bytes, but only {} bytes were written.", sizeof(value),
                                 writtenSize));
    }

    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::write(std::string_view const)
    void write(std::string_view const value)
    {
        auto length = value.size();
        write(length);

        auto const writtenSize = mOutStream.rdbuf()->sputn(value.data(), value.size());
        if (writtenSize != value.size())
            throwBinaryException(
                fmt_ns::format("Error writing data to stream.  Attempted to write {} bytes, but only {} bytes were written.", value.size(), writtenSize));
    }

    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::write(std::span<std::byte> const)
    void write(std::span<std::byte const> const value)
    {
        auto length = value.size();
        write(length);

        auto const writtenSize = mOutStream.rdbuf()->sputn(reinterpret_cast<const char*>(value.data()), value.size());
        if (writtenSize != value.size())
            throwBinaryException(fmt_ns::format("Error writing data to stream.  Attempted to write {} bytes, but only {} bytes were written.", value.size(),
                                 writtenSize));
    }

    /// Write a string literal to the serialisation.
    template <std::size_t N>
    void write(const char (&str)[N])
    {
        write(std::string_view(str, N - 1));
    }

private:
    std::ostream& mOutStream;
};

} // namespace morpheus::serialisation
