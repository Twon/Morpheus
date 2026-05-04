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

// template <concepts::Reader ReaderType>
// template <typename T, typename Allocator>
//[[nodiscard]] T ReadSerialiser<ReaderType>::deserialise(Allocator const& alloc)
//{
//     return mReader.template read<T>(alloc);
// }

template <concepts::Reader ReaderType>
template <typename T>
[[nodiscard]] void ReadSerialiser<ReaderType>::deserialise(T& value)
{
    serialisation::deserialise(*this, value);
}

template <concepts::Reader ReaderType>
template <typename T>
[[nodiscard]] T ReadSerialiser<ReaderType>::deserialise(std::string_view const key)
{
    auto const scope = makeScopedValue(mReader, key);
    return serialisation::deserialise.template operator()<ReadSerialiser<ReaderType>, T>(*this);
}

template <concepts::Reader ReaderType>
template <typename T>
[[nodiscard]] concurrency::Generator<T> ReadSerialiser<ReaderType>::sequence()
{
    auto const size = mReader.beginSequence();
    auto g = mReader.readElements<T>([this]() { return this->deserialise<T>(); }, size);

    for (auto&& item : g)
    {
        co_yield std::move(item);
    }

    mReader.endSequence();
}

template <concepts::Reader ReaderType>
template <typename T, typename Allocator>
[[nodiscard]] concurrency::Generator<T> ReadSerialiser<ReaderType>::sequence(Allocator const& alloc)
{
    auto const size = mReader.beginSequence();
    // For general types, we don't have a way to propagate the allocator to the elements
    // unless the element is also a container that takes an allocator, but we'd need
    // to know how to pass it.
    // For std::byte sequences, this will be handled by the optimization in ranges.hpp.
    auto g = mReader.readElements<T>([this]() { return this->deserialise<T>(); }, size);

    for (auto&& item : g)
    {
        co_yield std::move(item);
    }

    mReader.endSequence();
}

template <concepts::Reader ReaderType>
template <typename T>
[[nodiscard]] concurrency::Generator<T> ReadSerialiser<ReaderType>::sequence(std::string_view const key)
{
    auto const scope = makeScopedValue(mReader, key);
    auto gen = sequence<T>();
    for (auto&& item : gen)
    {
        co_yield std::move(item);
    }
}

} // namespace morpheus::serialisation
