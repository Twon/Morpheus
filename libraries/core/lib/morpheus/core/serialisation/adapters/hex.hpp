#pragma once

#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conformance/scan.hpp"
#include "morpheus/core/serialisation/exceptions.hpp"

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <string>

namespace morpheus::serialisation
{

/// \class Hex
///     A wrapper type for serialising a value as a hex string in textual formats.
template <typename T>
requires std::integral<T> or std::same_as<T, std::byte>
struct Hex
{
    T& value;
};

/// Deduction guide for the Hex wrapper.
template <typename T>
Hex(T&) -> Hex<T>;

/// Serialise a Hex wrapped value.
template <typename Serialiser, typename T>
requires(std::integral<T> or std::same_as<T, std::byte>)
void serialise(Serialiser& s, Hex<T> const& wrapper)
{
    if constexpr (Serialiser::isTextual())
    {
        if constexpr (sizeof(T) == 1)
            s.write(conf::fmt::format("0x{:02X}", static_cast<std::uint8_t>(wrapper.value)));
        else if constexpr (sizeof(T) == 2)
            s.write(conf::fmt::format("0x{:04X}", static_cast<std::uint16_t>(wrapper.value)));
        else if constexpr (sizeof(T) == 4)
            s.write(conf::fmt::format("0x{:08X}", static_cast<std::uint32_t>(wrapper.value)));
        else
            s.write(conf::fmt::format("0x{:016X}", static_cast<std::uint64_t>(wrapper.value)));
    }
    else
    {
        s.write(wrapper.value);
    }
}

/// Deserialise a Hex wrapped value.
template <typename Serialiser, typename T>
requires(std::integral<T> or std::same_as<T, std::byte>)
void deserialise(Serialiser& s, Hex<T> wrapper)
{
    if constexpr (Serialiser::isTextual())
    {
        auto const str = s.template read<std::string>();

        using Underlying = std::conditional_t<std::is_same_as_v<T, std::byte>, std::uint8_t, T>;

        auto result = conf::scan::scan<Underlying>(str, "{:/(?:0[xX])?([0-9a-fA-F]+)/}");
        if (result)
        {
            wrapper.value = static_cast<T>(result->value());
            return;
        }

        throw serialisation::serialisation_exception("Failed to parse hex value: " + str);
    }
    else
    {
        wrapper.value = s.template read<T>();
    }
}

} // namespace morpheus::serialisation
