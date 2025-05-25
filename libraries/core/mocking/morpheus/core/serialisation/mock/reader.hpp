#pragma once

#include <gmock/gmock.h>
#include <cstdint>
#include <cstddef>
#include <optional>
#include <span>
#include <string_view>
#include <string>
#include <vector>

namespace morpheus::serialisation::mock
{

/// \class Reader
///     Provides a mocks adhering to the concept morpheus::serialisation::concepts::Reader.
class Reader
{
public:
    /// \defgroup MockFunctions Mock Functions
    ///@{

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::isTextual()
    MOCK_METHOD(bool, isTextual, (), ());

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::beginComposite()
    MOCK_METHOD(void, beginComposite, (), ());
    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::endComposite()
    MOCK_METHOD(void, endComposite, (), ());
    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::beginValue()
    MOCK_METHOD(void, beginValue, (std::string_view), ());
    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::endValue()
    MOCK_METHOD(void, endValue, (), ());
    /// Begin reading a sequence of values.
    MOCK_METHOD(std::optional<std::size_t>, beginSequence, (), ());
    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::endSequence()
    MOCK_METHOD(void, endSequence, (), ());
    /// Begin reading a nullable value.
    MOCK_METHOD(bool, beginNullable, (), ());
    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::endNullable()
    MOCK_METHOD(void, endNullable, (), ());

    /// Reads a boolean type from the serialisation.
    MOCK_METHOD(bool, read, (bool), ());
    /// Reads a 8-bit unsigned integral type from the serialisation.
    MOCK_METHOD(std::uint8_t, read, (std::uint8_t), ());
    /// Reads a 8-bit integral type from the serialisation.
    MOCK_METHOD(std::int8_t, read, (std::int8_t), ());
    /// Reads a 16-bit unsigned integral type from the serialisation.
    MOCK_METHOD(std::uint16_t, read, (std::uint16_t), ());
    /// Reads a 16-bit integral type from the serialisation.
    MOCK_METHOD(std::int16_t, read, (std::int16_t), ());
    /// Reads a 32-bit unsigned integral type from the serialisation.
    MOCK_METHOD(std::uint32_t, read, (std::uint32_t), ());
    /// Reads a 32-bit integral type from the serialisation.
    MOCK_METHOD(std::int32_t, read, (std::int32_t), ());
    /// Reads a 64-bit unsigned integral type from the serialisation.
    MOCK_METHOD(std::uint64_t, read, (std::uint64_t), ());
    /// Reads a 64-bit integral type from the serialisation.
    MOCK_METHOD(std::int64_t, read, (std::int64_t), ());
    /// Reads a float type from the serialisation.
    MOCK_METHOD(float, read, (float), ());
    /// Reads a double type from the serialisation.
    MOCK_METHOD(double, read, (double), ());
    /// Reads a std::string_view type from the serialisation.
    MOCK_METHOD(std::string, read, (std::string_view), ());
    /// Reads a std::string type from the serialisation.
    MOCK_METHOD(std::string, read, (std::string), ());
    /// Reads a string literal type from the serialisation.
    MOCK_METHOD(std::string, read, (char const * const), ());
    /// Reads a blob of bytes from the serialisation.
    MOCK_METHOD(std::vector<std::byte>, read, (std::vector<std::byte>), ());
    ///@}

    /// Template wrapper around read which dispatchs to the correct concrete read method based on the type T.
    template<typename T>
    T read() requires requires(Reader r) { r.read(T{}); }
    {
        return read(T{});
    }
};

} // namespace morpheus::serialisation::mock
