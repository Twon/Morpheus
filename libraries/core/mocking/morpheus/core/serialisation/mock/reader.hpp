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
    MOCK_METHOD(bool, beginNullable, (), ());
    MOCK_METHOD(void, endNullable, (), ());

    MOCK_METHOD(bool, read, (bool), ());
    MOCK_METHOD(std::uint8_t, read, (std::uint8_t), ());
    MOCK_METHOD(std::int8_t, read, (std::int8_t), ());
    MOCK_METHOD(std::uint16_t, read, (std::uint16_t), ());
    MOCK_METHOD(std::int16_t, read, (std::int16_t), ());
    MOCK_METHOD(std::uint32_t, read, (std::uint32_t), ());
    MOCK_METHOD(std::int32_t, read, (std::int32_t), ());
    MOCK_METHOD(std::uint64_t, read, (std::uint64_t), ());
    MOCK_METHOD(std::int64_t, read, (std::int64_t), ());
    MOCK_METHOD(float, read, (float), ());
    MOCK_METHOD(double, read, (double), ());
    MOCK_METHOD(std::string, read, (std::string_view), ());
    MOCK_METHOD(std::string, read, (std::string), ());
    MOCK_METHOD(std::vector<std::byte>, read, (std::span<std::byte>), ());
    ///@}

    template<typename T>
    T read() requires requires(Reader r) { r.read(T{}); }
    {
        return read(T{});
    }
};

} // namespace morpheus::serialisation::mock