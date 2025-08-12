#pragma once

// IWYU pragma: always_keep
#include "morpheus/core/meta/is_specialisation.hpp"
#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"
#include <tuple>

namespace morpheus::serialisation::detail
{

template <typename T>
concept IsStdTuple = meta::IsSpecialisationOf<std::tuple, T>;

template <concepts::WriteSerialiser Serialiser, concepts::WriteSerialisable... T>
void serialise(Serialiser& serialiser, std::tuple<T...> const& value)
{
    constexpr auto size = std::tuple_size<std::tuple<T...>>::value;
    serialiser.writer().beginSequence(size);
    [&]<std::size_t... Indexes>(std::index_sequence<Indexes...>) { (serialiser.serialise(std::get<Indexes>(value)), ...); }(std::make_index_sequence<size>());
    serialiser.writer().endSequence();
}

template <concepts::ReadSerialiser Serialiser, IsStdTuple T>
T deserialise(Serialiser& serialiser)
{
    constexpr std::size_t size = std::tuple_size<T>::value;

    auto const scope = makeScopedSequence(serialiser.reader(), std::tuple_size<T>::value);
    return [&serialiser]<std::size_t... Indexes>(std::index_sequence<Indexes...>)
    {
        // More work required to support std::tuples containing references.
        static_assert((!std::is_reference_v<std::tuple_element_t<Indexes, T>> || ...));
        return T{serialiser.template deserialise<std::tuple_element_t<Indexes, T>>()...};
    }(std::make_index_sequence<size>());
}

} // namespace morpheus::serialisation::detail
