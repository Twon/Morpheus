#pragma once

#include "core/conformance/ranges.hpp"
#include "core/serialisation/concepts/read_serialiser.hpp"
#include "core/serialisation/concepts/read_serialisable.hpp"
#include "core/serialisation/concepts/write_serialiser.hpp"
#include "core/serialisation/concepts/write_serialisable.hpp"

namespace morpheus::serialisation::detail
{

//template <typename T>
//concept IsRange = meta::IsSpecialisationOf<std::tuple, T>;

template<concepts::WriteSerialiser Serialiser, ranges::range T>
void serialise(Serialiser& serialiser, auto const& range)
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