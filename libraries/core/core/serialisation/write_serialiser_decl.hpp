#pragma once

#include "core/meta/concepts/constructible.hpp"
#include "core/serialisation/concepts/writer.hpp"

#include <string_view>
#include <type_traits>
#include <utility>

namespace morpheus::serialisation
{

template<concepts::Writer WriterType>
class WriteSerialiser
{
public:
    template<meta::concepts::DefaultConstructible T = WriterType>
    WriteSerialiser() noexcept(std::is_nothrow_default_constructible_v<T>) 
    {}

    template<typename... Args>
    requires(std::is_constructible_v<WriterType, Args...>)
    WriteSerialiser(Args&&... args) noexcept(meta::concepts::NothrowConstructible<WriterType, Args...>)
    :   mWriter(std::forward<Args>(args)...) 
    {}

#if (__cpp_explicit_this_parameter >= 202110)
    template<typename Self>
    [[nodiscard]] auto& writer(this Self&& self) noexcept { return self.mWriter; }
#else
    [[nodiscard]] WriterType& writer() noexcept { return mWriter; }
    [[nodiscard]] WriterType const& writer() const noexcept { return mWriter; }
#endif // (__cpp_explicit_this_parameter >= 202110)

    /// \name Serialise
    ///     Custom serialise function specialisations should serialise sub-members via the writes serialisers
    ///     methods.  This allows breaking of cirular dependencies in the dispatching of serialisation calls and delays
    ///     look up of the actual serialisation call to the second phase of the two-phase lookup. With the dependency
    ///     broken the actual underlying calls dispatch to the serialise customisation point object which then finds
    ///     the correct call via ADL dispatch.
    ///@{
    /// Serialise a single value
    /// \tparam T The underlying type of value to serialise.
    /// \param[in] value The value to serialise.
    template<typename T>
    void serialise(T const& value);

    /// Serialise a key value pair
    /// \tparam T The underlying type of value to serialise.
    /// \param[in] key The key to serialise.
    /// \param[in] value The value to serialise.
    template<typename T>
    void serialise(std::string_view const key, T const& value);
    ///@}
private:
    WriterType mWriter;
};

}