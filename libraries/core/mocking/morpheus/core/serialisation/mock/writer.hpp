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
    MOCK_METHOD(bool, isTextual, (), ());

    MOCK_METHOD(void, beginComposite, (), ());
    MOCK_METHOD(void, endComposite, (), ());
    MOCK_METHOD(void, beginValue, (std::string_view), ());
    MOCK_METHOD(void, endValue, (), ());
    MOCK_METHOD(void, beginSequence, (std::optional<std::size_t>), ());
    MOCK_METHOD(void, endSequence, (), ());
    MOCK_METHOD(void, beginNullable, (bool), ());
    MOCK_METHOD(void, endNullable, (), ());

    MOCK_METHOD(void, write, (bool), ());
    MOCK_METHOD(void, write, (std::uint8_t), ());
    MOCK_METHOD(void, write, (std::int8_t), ());
    MOCK_METHOD(void, write, (std::uint16_t), ());
    MOCK_METHOD(void, write, (std::int16_t), ());
    MOCK_METHOD(void, write, (std::uint32_t), ());
    MOCK_METHOD(void, write, (std::int32_t), ());
    MOCK_METHOD(void, write, (std::uint64_t), ());
    MOCK_METHOD(void, write, (std::int64_t), ());
    MOCK_METHOD(void, write, (float), ());
    MOCK_METHOD(void, write, (double), ());
    MOCK_METHOD(void, write, (std::string_view), ());
    MOCK_METHOD(void, write, (std::span<std::byte>), ());
    ///@}
};

} // namespace morpheus::serialisation::mock