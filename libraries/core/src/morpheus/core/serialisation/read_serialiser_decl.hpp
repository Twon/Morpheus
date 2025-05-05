#pragma once

#include "morpheus/core/base/scoped_action.hpp"
#include "morpheus/core/meta/concepts/constructible.hpp"
#include "morpheus/core/serialisation/concepts/reader.hpp"

#include <cstddef>
#include <optional>
#include <string_view>
#include <type_traits>

namespace morpheus::serialisation
{

auto makeScopedValue(concepts::Reader auto& reader, std::string_view const key)
{
    return ScopedAction([&reader, key] { reader.beginValue(key); }, [&reader] { reader.endValue(); } );
}

auto makeScopedSequence(concepts::Reader auto& reader, std::optional<std::size_t> const = std::nullopt)
{
    return ScopedAction([&reader] { return reader.beginSequence(); }, [&reader] { reader.endSequence(); } );
}

auto makeScopedComposite(concepts::Reader auto& reader)
{
    return ScopedAction([&reader] { reader.beginComposite(); }, [&reader] { reader.endComposite(); } );
}

auto makeScopedNullable(concepts::Reader auto& reader)
{
    return ScopedAction([&reader] { return reader.beginNullable(); }, [&reader] { reader.endNullable(); } );
}

/// \class ReadSerialiser
/// \tparam ReaderType The type of underlying reader for serialisation.
template<concepts::Reader ReaderType>
class ReadSerialiser
{
public:
    /// Constructs a ReadSerialiser when the underlying reader supports default construction.
    template<meta::concepts::DefaultConstructible T = ReaderType>
    ReadSerialiser() noexcept(meta::concepts::DefaultNothrowConstructible<T>)
    {}

    template<typename... Args>
    requires(std::is_constructible_v<ReaderType, Args...>)
    ReadSerialiser(Args&&... args) noexcept(meta::concepts::NothrowConstructible<ReaderType, Args...>)
    :   mReader(std::forward<Args>(args)...)
    {}

#if (__cpp_explicit_this_parameter >= 202110)
    /// Access the underlying reader.
    template<typename Self>
    [[nodiscard]] auto& reader(this Self&& self) noexcept { return self.mReader; }
#else
    /// Access the underlying reader.
    [[nodiscard]] ReaderType& reader() noexcept { return mReader; }
    /// Access the underlying reader.
    [[nodiscard]] ReaderType const& reader() const noexcept { return mReader; }
#endif // (__cpp_explicit_this_parameter >= 202110)

    /// \name Deserialise
    ///     Custom deserialise function specialisations should deserialise sub-members via the readers deserialisers
    ///     methods.  This allows breaking of circular dependencies in the dispatching of deserialisation calls and
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
    ReaderType mReader; ///< The underlying reading for serialising fundamental types.
};

}
