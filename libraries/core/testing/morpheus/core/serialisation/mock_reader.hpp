#pragma once

#include <gmock/gmock.h>
#include <cstdint>
#include <optional>
#include <span>
#include <string_view>

namespace morpheus::serialisation::mock
{

/// \class Reader
///     Provides a mocks adhering to the concept \ref morpheus::serialisation::concepts::Reader.
class Reader
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

    MOCK_METHOD(void, read, (bool), ());
    MOCK_METHOD(void, read, (std::uint8_t), ());
    MOCK_METHOD(void, read, (std::int8_t), ());
    MOCK_METHOD(void, read, (std::uint16_t), ());
    MOCK_METHOD(void, read, (std::int16_t), ());
    MOCK_METHOD(void, read, (std::uint32_t), ());
    MOCK_METHOD(void, read, (std::int32_t), ());
    MOCK_METHOD(void, read, (std::uint64_t), ());
    MOCK_METHOD(void, read, (std::int64_t), ());
    MOCK_METHOD(void, read, (float), ());
    MOCK_METHOD(void, read, (double), ());
    MOCK_METHOD(void, read, (std::string_view), ());
    MOCK_METHOD(void, read, (std::span<std::byte>), ());
    ///@}

    template<typename T>
    T read() requires requires { read(T{}); }
    {
        read(T{});
        return T{};
    }
};

} // namespace morpheus::serialisation::mock