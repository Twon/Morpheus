#pragma once

#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"
#include "morpheus/core/meta/concepts/string.hpp"

namespace morpheus::serialisation::detail
{

template <typename T>
concept IsRange = ranges::range<T> and not (meta::IsString<T> or meta::IsStringView<T>);

template<concepts::WriteSerialiser Serialiser>
void serialise(Serialiser& serialiser, IsRange auto const& range)
{
    serialiser.serialise(ranges::size(range), [&]()
    {
        ranges::for_each(range, [&serialiser](auto const& element) { serialiser.serialise(element); });
    });
}

template<concepts::ReadSerialiser Serialiser, ranges::range T>
T deserialise(Serialiser& serialiser)
{
    constexpr std::size_t size = std::tuple_size<T>::value;

    auto const scope = makeScopedSequence(serialiser.reader(), std::tuple_size<T>::value);
    return[&serialiser]<std::size_t... Indexes>(std::index_sequence<Indexes...> )
    {
        // More work required to support std::tuples containing references.
        static_assert((!std::is_reference_v<std::tuple_element_t<Indexes, T>> || ...));
        return T{ serialiser.template deserialise<std::tuple_element_t<Indexes, T>>()... };
    }(std::make_index_sequence<size>());
}

} // morpheus::serialisation