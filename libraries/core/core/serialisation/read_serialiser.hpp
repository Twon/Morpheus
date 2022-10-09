#pragma once

#include "core/meta/concepts/constructible.hpp"
#include "core/serialisation/concepts/reader.hpp"
#include <type_traits>

namespace morpheus::serialisation
{

template<concepts::Reader ReaderType>
class ReadSerialiser
{
public:
    template<meta::concepts::DefaultConstructible T = ReaderType>
    ReadSerialiser() noexcept(meta::concepts::DefaultNothrowConstructible<T>) {}

    template<typename... Args>
    requires(std::is_constructible_v<ReaderType, Args...>)
    ReadSerialiser(Args&&... args) : mReader(std::forward<Args>(args)...) {}

    [[nodiscard]] ReaderType& reader() noexcept { return mReader; }
    [[nodiscard]] ReaderType const& reader() const noexcept { return mReader; }

    template<typename T>
    requires std::is_arithmetic_v<T>
    T deserialise()
    {
        return deserialiseDispatch<ReadSerialiser<ReaderType>, T>(*this);
    }
private:
    ReaderType mReader;
};

}