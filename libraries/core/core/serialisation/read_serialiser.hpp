#pragma once

#include "core/meta/concepts/constructible.hpp"
#include "core/serialisation/concepts/reader.hpp"
#include "core/serialisation/read_serialiser_decl.hpp"
#include "core/serialisation/serialise.hpp"


#include <string_view>
#include <type_traits>

namespace morpheus::serialisation
{

template<concepts::Reader ReaderType>
template<typename T>
[[nodiscard]] T ReadSerialiser<ReaderType>::deserialise()
{
    return serialisation::deserialise.template operator()<ReadSerialiser<ReaderType>, T>(*this);
}

template<concepts::Reader ReaderType>
template<typename T>
[[nodiscard]] T ReadSerialiser<ReaderType>::deserialise(std::string_view const key)
{
    auto const scope = makeScopedValue(mReader, key);
    return serialisation::deserialise.template operator()<ReadSerialiser<ReaderType>, T>(*this);
}

template<concepts::Reader ReaderType>
template<typename T>
[[nodiscard]] T ReadSerialiser<ReaderType>::deserialise(std::size_t size, std::invocable auto f)
{
    auto const sequence = makeScopedSequence(*this, size);

}

template<concepts::Reader ReaderType>
template<typename T>
[[nodiscard]] T ReadSerialiser<ReaderType>::deserialise(std::invocable auto f)
{

}

template<concepts::Reader ReaderType>
template<typename T>
[[nodiscard]] T ReadSerialiser<ReaderType>::deserialise(bool const null, std::invocable auto f)
{

}

}