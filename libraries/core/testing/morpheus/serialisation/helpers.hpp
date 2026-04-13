#include "morpheus/core/serialisation/serialisers.hpp"
#include "morpheus/core/serialisation/write_serialiser.hpp"

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>

#include <cstddef>
#if __has_include(<spanstream>)
    #include <spanstream>
#endif
#include <vector>

namespace morpheus::serialisation::testing
{

template <typename... Ts>
constexpr std::array<std::byte, sizeof...(Ts)> makeBytes(Ts&&... args) noexcept
{
    return {std::byte(std::forward<Ts>(args))...};
}

template <typename... Ts>
constexpr std::array<char, sizeof...(Ts)> makeCharArray(Ts&&... args) noexcept
{
    return {char(std::forward<Ts>(args))...};
}

/// Serialiser a value to a binary buffer.
/// \param[in] value The value to be serialised.
/// \return The binary blob containing the serialised form of the input value.
std::vector<char> serialise(auto const& value)
{
    using namespace boost::iostreams;
    std::vector<char> storage;
    back_insert_device sink{storage};
    stream os{sink};
    BinaryWriteSerialiser serialiser{os};
    serialiser.serialise(value);
    return storage;
}

/// Serialise a value to a binary buffer with limited space.  This is useful for testing or error cases such as testing
/// condition where storage is exhuasted.
///
/// \tparam Size The size of the static buffer.
/// \param[in] value The value to be serialised.
/// \return The binary blob containing the serialised form of the input value.
template <std::size_t Size>
std::array<char, Size> serialiseWithLimitedSpace(auto const& value)
{
    using namespace boost::iostreams;
    std::array<char, Size> storage = {};
    array_sink sink{storage.data(), storage.size()};
    stream os{sink};
    BinaryWriteSerialiser serialiser{os};
    serialiser.serialise(value);
    return storage;
}

/// Deserialise a value to a binary buffer with limited space.  This is useful for testing or error cases such as
/// testing condition where storage is exhuasted.
///
/// \tparam T The type of value to be deserialised.
/// \param[in] storage The binary blob representing the serialised form of the type.
/// \returns The deserialised value.
template <typename T>
T deserialiseWithIoStream(auto const& storage)
{
    using namespace boost::iostreams;
    array_source source{storage.data(), storage.size()};
    stream is{source};
    BinaryReadSerialiser serialiser{is};
    return serialiser.deserialise<T>();
}

/// Serialise a value to a binary buffer with limited space.  This is useful for testing or error cases such as testing
/// condition where storage is exhuasted.
///
/// \tparam Size The size of the static buffer.
/// \param[in] value The value to be serialised.
/// \return The binary blob containing the serialised form of the input value.
#if (__cpp_lib_spanstream >= 202106L)
template <std::size_t Size>
std::array<char, Size> serialiseWithSpanStream(auto const& value)
{
    std::array<char, Size> storage;
    std::span view{storage};
    std::ospanstream stream{view};
    BinaryWriteSerialiser serialiser{stream};
    serialiser.serialise(value);
    return storage;
}

/// Deserialise a value to a binary buffer with limited space.  This is useful for testing or error cases such as
/// testing condition where storage is exhuasted.
///
/// \tparam T The type of value to be deserialised.
/// \param[in] storage The binary blob representing the serialised form of the type.
/// \returns The deserialised value.
template <typename T>
T deserialiseWithSpanStream(auto const& storage)
{
    std::span view{storage};
    std::ispanstream stream{view};
    BinaryReadSerialiser serialiser{stream};
    return serialiser.deserialise<T>();
}
#endif

/// Deserialised a value from a binary blob of data.
///
/// \tparam T The type of value to be deserialised.
/// \param[in] value The binary blob representing the serialised form of the type.
/// \returns The deserialised value.
template <typename T>
T deserialise(std::vector<char> const& value)
{
    using namespace boost::iostreams;
    array_source source{value.data(), value.size()};
    stream is{source};
    BinaryReadSerialiser serialiser{is};
    return serialiser.deserialise<T>();
}

/// Serialises an object to a binary blob and then deserialise back into the original form.
///
/// \tparam T The type of value to be serialised/deserialised.
/// \param[in] value The value to be serialised then deserialised.
/// \returns The resulting deserialised value.
template <typename T>
T roundtrip(T const& value)
{
    return deserialise<T>(serialise(value));
}

} // namespace morpheus::serialisation::testing
