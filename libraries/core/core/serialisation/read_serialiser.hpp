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
    auto const scope = ScopedValue(mReader, key);
    return serialisation::deserialise.template operator()<ReadSerialiser<ReaderType>, T>(*this);
}


}