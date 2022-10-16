#pragma once

#include "core/meta/concepts/constructible.hpp"
#include "core/serialisation/concepts/reader.hpp"

#include <string_view>
#include <type_traits>

namespace morpheus::serialisation
{

template<concepts::Reader ReaderType>
class ScopedValue
{
public:
    constexpr ScopedValue(ReaderType& reader, std::string_view const key) 
    :   mReader(reader) 
    {
        mReader.beginValue(key);
    }

    constexpr ScopedValue(ScopedValue const&) = delete;
    constexpr ScopedValue(ScopedValue&&) = delete;

    constexpr ScopedValue operator=(ScopedValue const&) = delete;
    constexpr ScopedValue operator=(ScopedValue&&) = delete;

    constexpr ~ScopedValue()
    {
        mReader.endValue();
    }

private:
    ReaderType& mReader;
};

template<concepts::Reader ReaderType>
class ReadSerialiser
{
public:
    template<meta::concepts::DefaultConstructible T = ReaderType>
    ReadSerialiser() noexcept(meta::concepts::DefaultNothrowConstructible<T>) 
    {}

    template<typename... Args>
    requires(std::is_constructible_v<ReaderType, Args...>)
    ReadSerialiser(Args&&... args) noexcept(meta::concepts::NothrowConstructible<ReaderType, Args...>)
    :   mReader(std::forward<Args>(args)...) 
    {}

    [[nodiscard]] ReaderType& reader() noexcept { return mReader; }
    [[nodiscard]] ReaderType const& reader() const noexcept { return mReader; }

    template<typename T>
//    requires std::is_arithmetic_v<T>
    [[nodiscard]] T deserialise()
    {
        return deserialiseDispatch<ReadSerialiser<ReaderType>, T>(*this);
    }

    template<typename T>
    [[nodiscard]] T deserialise(std::string_view const key)
    {
        auto const scope = ScopedValue(mReader, key);
        return deserialiseDispatch<ReadSerialiser<ReaderType>, T>(*this);
    }

private:
    ReaderType mReader;
};

}