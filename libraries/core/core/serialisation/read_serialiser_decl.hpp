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

    /// \name Deserialise
    ///     Custom deserialise function specialisations should deserialise sub-members via the writes serialisers
    ///     methods.  This allows breaking of cirular dependencies in the dispatching of deserialisation calls and
    ///     delays look up of the actual deserialisation call to the second phase of the two-phase lookup. With the
    ///     dependency broken the actual underlying calls dispatch to the deserialise customisation point object which
    ///     then finds the correct call via ADL dispatch.
    ///@{
    /// Deserialise a single value
    /// \tparam T The underlying type of value to deserialise.
    /// \return The deserialises value.
    template<typename T>
    [[nodiscard]] T deserialise();

    /// Deserialise a key value pair
    /// \tparam T The underlying type of value to deserialise.
    /// \param[in] key The key to serialise.
    /// \return The deserialises value.
    template<typename T>
    [[nodiscard]] T deserialise(std::string_view const key);
    ///@}
private:
    ReaderType mReader;
};

}