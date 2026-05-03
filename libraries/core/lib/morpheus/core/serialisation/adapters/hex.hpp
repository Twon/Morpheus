#pragma once

#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conformance/scan.hpp"
#include "morpheus/core/serialisation/concepts/hexable.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"
#include "morpheus/core/serialisation/exceptions.hpp"

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <string>
#include <type_traits>

namespace morpheus::serialisation
{

/// \class Hex
///     A wrapper type for serialising a value as a hex string in textual formats.
template <concepts::Hexable T>
struct Hex
{
    T& value;
};

/// Deduction guide for the Hex wrapper.
template <typename T>
Hex(T&) -> Hex<T>;

namespace detail
{

/// Serialise a Hex wrapped value via a WriteSerialiser wrapper.
template <concepts::WriteSerialiser Serialiser, concepts::Hexable T>
void serialise(Serialiser& s, Hex<T> const& wrapper)
{
    if constexpr (Serialiser::Writer::isTextual())
    {
        s.writer().write(conf::fmt::format("{}", wrapper));
    }
    else
    {
        s.writer().write(wrapper.value);
    }
}

/// Deserialise a Hex wrapped value via a ReadSerialiser wrapper.
template <concepts::ReadSerialiser Serialiser, concepts::Hexable T>
void deserialise_to(Serialiser& s, Hex<T>&& wrapper)
{
    if constexpr (Serialiser::Reader::isTextual())
    {
        auto const str = s.reader().template read<std::string>();

        // Because Hex is a reference wrapper, we need to use the underlying type for parsing to a value
        // to avoid issues with initialisation of reference type, which is not supported by std::scan.
        // Scanning of byte or chars is not allowed, so we use uint8_t as the underlying type for parsing
        // and then cast back to the original type.
        using Underlying = std::conditional_t<std::disjunction_v<std::is_same<T, std::byte>, std::is_same<T, std::int8_t>>, std::uint8_t, T>;

        auto result = conf::scan::scan<Underlying>(str, "{:x}");
        if (result)
        {
            wrapper.value = static_cast<T>(result->value());
            return;
        }

        throwJsonException("Failed to parse hex value: {}", str);
    }
    else
    {
        wrapper.value = s.reader().template read<T>();
    }
}

} // namespace detail

} // namespace morpheus::serialisation

/// Specialisation of the formatter for morpheus::serialisation::Hex to format it as a string.
template <morpheus::serialisation::concepts::Hexable T, typename CharT>
struct morpheus::conf::fmt::formatter<morpheus::serialisation::Hex<T>, CharT> : morpheus::conf::fmt::formatter<std::string, CharT>
{
    /// Format the morpheus::application::Hex as a string.
    /// \tparam Context The type of the format context.
    /// \param value The version value to format.
    /// \param context The format context.
    template <typename Context>
    constexpr auto format(morpheus::serialisation::Hex<T> const& value, Context& context) const
    {
        if constexpr (sizeof(T) == 1)
            return morpheus::conf::fmt::format_to(context.out(), "0x{:02X}", static_cast<std::uint8_t>(value.value));
        else if constexpr (sizeof(T) == 2)
            return morpheus::conf::fmt::format_to(context.out(), "0x{:04X}", value.value);
        else if constexpr (sizeof(T) == 4)
            return morpheus::conf::fmt::format_to(context.out(), "0x{:08X}", value.value);
        else if constexpr (sizeof(T) == 8)
            return morpheus::conf::fmt::format_to(context.out(), "0x{:016X}", value.value);
        else
            static_assert(sizeof(T) > 8, "Extend for support of deserialisation of integers greater than 64-bits for Hex<T>");
    }
};
