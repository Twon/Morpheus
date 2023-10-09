#pragma once

#include <gmock/gmock.h>
#include <cstdint>
#include <optional>
#include <span>
#include <string_view>

namespace morpheus::serialisation::mock
{

/// \class Writer
///     Provides a mocks adhering to the concept \ref morpheus::serialisation::concepts::Writer.
class Writer
{
public:
    /// \defgroup MockFunctions Mock Functions
    ///@{

    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::isTextual()
    MOCK_METHOD(bool, isTextual, (), ());

    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::beginComposite()
    MOCK_METHOD(void, beginComposite, (), ());
    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::endComposite()
    MOCK_METHOD(void, endComposite, (), ());
    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::beginValue()
    MOCK_METHOD(void, beginValue, (std::string_view), ());
    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::endValue()
    MOCK_METHOD(void, endValue, (), ());
    /// Begin writing a sequence of values.
    MOCK_METHOD(void, beginSequence, (std::optional<std::size_t>), ());
    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::endSequence()
    MOCK_METHOD(void, endSequence, (), ());
    /// Begin writing a nullable value.
    MOCK_METHOD(void, beginNullable, (bool), ());
    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::endNullable()
    MOCK_METHOD(void, endNullable, (), ());

    /// \copydoc morpheus::serialisation::JsonWriter::write(bool)
    MOCK_METHOD(void, write, (bool), ());
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::uint8_t)
    MOCK_METHOD(void, write, (std::uint8_t), ());
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::int8_t)
    MOCK_METHOD(void, write, (std::int8_t), ());
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::uint16_t)
    MOCK_METHOD(void, write, (std::uint16_t), ());
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::int16_t)
    MOCK_METHOD(void, write, (std::int16_t), ());
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::uint32_t)
    MOCK_METHOD(void, write, (std::uint32_t), ());
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::int32_t)
    MOCK_METHOD(void, write, (std::int32_t), ());
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::uint64_t)
    MOCK_METHOD(void, write, (std::uint64_t), ());
    /// \copydoc morpheus::serialisation::JsonWriter::write(std::uint64_t)
    MOCK_METHOD(void, write, (std::int64_t), ());
    /// \copydoc morpheus::serialisation::JsonWriter::write(float)
    MOCK_METHOD(void, write, (float), ());
    /// \copydoc morpheus::serialisation::JsonWriter::write(double)
    MOCK_METHOD(void, write, (double), ());
    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::write(std::string_view const)
    MOCK_METHOD(void, write, (std::string_view), ());
    /// \copydoc morpheus::serialisation::concepts::WriterArchtype::write(std::span<std::byte> const)
    MOCK_METHOD(void, write, (std::span<std::byte>), ());
    /// Write a string to the serialisation.
    MOCK_METHOD(void, write, (char const* const), ());
    ///@}
};

} // namespace morpheus::serialisation::mock
