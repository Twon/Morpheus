#pragma once

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
    static constexpr bool isTextual() { return false; }

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::beginComposite()
    void beginComposite(){}

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::endComposite()
    void endComposite(){}

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::beginValue()
    void beginValue(std::string_view const) {}

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::endValue()
    void endValue(){}

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::beginSequence()
    std::optional<std::size_t> beginSequence()
    {
        return read<std::size_t>();
    }

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::endSequence()
    void endSequence(){}

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::beginNullable()
    bool beginNullable()
    {
        return read<bool>();
    }

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::endNullable()
    void endNullable(){}

    template <typename T>
    requires std::integral<T> or std::floating_point<T>
    T read()
    {
        T value = {};
        auto const readSize = mInStream.rdbuf()->sgetn(reinterpret_cast<char*>(&value), sizeof(value));
        if (readSize != sizeof(value))
            throwBinaryException(
                fmt_ns::format("Error reading data from stream.  Attempted to read {} bytes, but only {} bytes were read.", sizeof(value), readSize));
        return value;
    }

    // clang-format off
    template <typename T>
    requires std::is_same_v<T, std::string>
    T read()
    {
        std::size_t length = read<std::size_t>();
        T value(length, '\0');
        auto const readSize = mInStream.rdbuf()->sgetn(value.data(), value.size());
        if (readSize != value.size())
            throwBinaryException(
                fmt_ns::format("Error reading data from stream.  Attempted to read {} bytes, but only {} bytes were read.", value.size(), readSize));
        return value;
    }

    template <typename T>
    requires std::is_same_v<T, std::vector<std::byte>>
    T read()
    {
        std::size_t length = read<std::size_t>();
        T value(length);
        auto const readSize = mInStream.rdbuf()->sgetn(reinterpret_cast<char*>(value.data()), value.size());
        if (readSize != value.size())
            throwBinaryException(
                fmt_ns::format("Error reading data from stream.  Attempted to read {} bytes, but only {} bytes were read.", value.size(), readSize));
        return value;
    }
    // clang-format on


private:
    std::istream& mInStream;
};

} // namespace morpheus::serialisation
