#pragma once

#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/core/meta/concepts/string.hpp"
#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"

namespace morpheus::serialisation::detail
{

/// \var isEnabledForRangeSerialisation
///     To enable serialisation for any type meeting the concept of a range then enable serialisation by specialising and enabling this value.
template <typename T>
constexpr bool isEnabledForRangeSerialisation = false;

/// \concept IsRange
///   For the purpose of serialisation of ranges we want to know that a given type is range, but also that we explicityly want to opt in as a Range
///   compatible type.  This is because certain type which already count as ranges are already handled within the framework, mainly strings.
///   Rather than special case ignoring strings an potentially other types the user must opt in by specialising \ref isEnabledForRangeSerialisation
///   for types that should be included for range support.
template <typename T>
concept IsRange = ranges::range<T> and isEnabledForRangeSerialisation<T>;

template <concepts::WriteSerialiser Serialiser>
void serialise(Serialiser& serialiser, IsRange auto const& range)
{
    serialiser.writer().beginSequence(ranges::size(range));
    ranges::for_each(range, [&serialiser](auto const& element) { serialiser.serialise(element); });
    serialiser.writer().endSequence();
}

template <concepts::ReadSerialiser Serialiser, ranges::range T>
T deserialise(Serialiser& serialiser)
{
    constexpr std::size_t size = std::tuple_size<T>::value;

    auto const scope = makeScopedSequence(serialiser.reader(), std::tuple_size<T>::value);
    return [&serialiser]<std::size_t... Indexes>(std::index_sequence<Indexes...>)
    {
        // More work required to support std::tuples containing references.
        static_assert((!std::is_reference_v<std::tuple_element_t<Indexes, T>> || ...));
        return T{serialiser.template deserialise<std::tuple_element_t<Indexes, T>>()...};
    }
    (std::make_index_sequence<size>());
}

} // namespace morpheus::serialisation::detail