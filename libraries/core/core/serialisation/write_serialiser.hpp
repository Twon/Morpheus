#pragma once

#include "core/meta/concepts/constructible.hpp"
#include "core/serialisation/concepts/writer.hpp"
#include "core/serialisation/serialise.hpp"
#include <type_traits>

namespace morpheus::serialisation
{

/// \class WriteSerialiser
/// 
/// \tparam WriterType
/// 

template<concepts::Writer WriterType>
class WriteSerialiser
{
public:
    template<meta::concepts::DefaultConstructible T = WriterType>
    WriteSerialiser() noexcept(std::is_nothrow_default_constructible_v<T>) {}

    template<typename... Args>
    requires(std::is_constructible_v<WriterType, Args...>)
    WriteSerialiser(Args&&... args) : mWriter(std::forward<Args>(args)...) {}

#if (__cpp_explicit_this_parameter >= 202110)
    template<typename Self>
    [[nodiscard]] auto& writer(this Self&& self) noexcept { return self.mWriter; }
#else
    [[nodiscard]] WriterType& writer() noexcept { return mWriter; }
    [[nodiscard]] WriterType const& writer() const noexcept { return mWriter; }
#endif // (__cpp_explicit_this_parameter >= 202110)

    template<typename T>
    void serialise(T const& value)
    {
        serialiseDispatch(*this, value);
    }
private:
    WriterType mWriter;
};

}