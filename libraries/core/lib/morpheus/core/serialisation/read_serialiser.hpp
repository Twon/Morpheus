#pragma once

#include "morpheus/core/serialisation/concepts/reader.hpp"
#include "morpheus/core/serialisation/read_serialiser_decl.hpp"
#include "morpheus/core/serialisation/serialise.hpp"

#include <string_view>
#include <type_traits>

namespace morpheus::serialisation
{

template <concepts::Reader ReaderType>
template <typename T>
[[nodiscard]] T ReadSerialiser<ReaderType>::deserialise()
{
    return serialisation::deserialise.template operator()<ReadSerialiser<ReaderType>, T>(*this);
}

template <concepts::Reader ReaderType>
template <typename T>
[[nodiscard]] T ReadSerialiser<ReaderType>::deserialise(std::string_view const key)
{
    auto const scope = makeScopedValue(mReader, key);
    return serialisation::deserialise.template operator()<ReadSerialiser<ReaderType>, T>(*this);
}

} // namespace morpheus::serialisation
