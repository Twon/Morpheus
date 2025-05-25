#pragma once

#include "morpheus/core/serialisation/concepts/reader_archetype.hpp"
#include "morpheus/core/serialisation/exceptions.hpp"

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <type_traits>

namespace morpheus::serialisation
{

class BinaryReader
{
public:
    BinaryReader(std::istream& inStream)
    : mInStream(inStream)
    {}

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::isTextual()
    static constexpr bool isTextual() noexcept { return false; }

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::beginComposite()
    void beginComposite() noexcept {}

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::endComposite()
    void endComposite() noexcept {}

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::beginValue(std::string_view const)
    void beginValue(std::string_view const) noexcept {}

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::endValue()
    void endValue() noexcept {}

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::beginSequence()
    std::optional<std::size_t> beginSequence()
    {
        return read<std::size_t>();
    }

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::endSequence()
    void endSequence() noexcept {}

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::beginNullable()
    bool beginNullable()
    {
        return read<bool>();
    }

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::endNullable()
    void endNullable() noexcept {}

    // Work around for Doxygen duplicate symbols bug, this is now fixed in Doyxgn 1.14.0: https://github.com/doxygen/doxygen/commit/64d0cb7f695b2ebe63131c06b7762c1f75212c28
    /// @cond INTERNAL
    /// Reads a integral type, a float or double type from the serialisation.
    template <typename T>
    requires std::integral<T> or std::floating_point<T>
    T read()
    {
        T value = {};
        auto const readSize = static_cast<std::size_t>(mInStream.rdbuf()->sgetn(reinterpret_cast<char*>(&value), sizeof(value)));
        if (readSize != sizeof(value))
            throwBinaryException(
                fmt_ns::format("Error reading data from stream.  Attempted to read {} bytes, but only {} bytes were read.", sizeof(value), readSize));
        return value;
    }

    // clang-format off
    /// Reads a string type from the serialisation.
    template <typename T>
    requires std::is_same_v<T, std::string>
    T read()
    {
        std::size_t length = read<std::size_t>();
        T value(length, '\0');
        auto const readSize = static_cast<std::size_t>(mInStream.rdbuf()->sgetn(value.data(), value.size()));
        if (readSize != value.size())
            throwBinaryException(
                fmt_ns::format("Error reading data from stream.  Attempted to read {} bytes, but only {} bytes were read.", value.size(), readSize));
        return value;
    }

    /// Reads a stream of bytes from the serialisation.
    template <typename T>
    requires std::is_same_v<T, std::vector<std::byte>>
    T read()
    {
        std::size_t length = read<std::size_t>();
        T value(length);
        auto const readSize = static_cast<std::size_t>(mInStream.rdbuf()->sgetn(reinterpret_cast<char*>(value.data()), value.size()));
        if (readSize != value.size())
            throwBinaryException(
                fmt_ns::format("Error reading data from stream.  Attempted to read {} bytes, but only {} bytes were read.", value.size(), readSize));
        return value;
    }
    // clang-format on
    /// @endcond

private:
    std::istream& mInStream;
};

} // namespace morpheus::serialisation
