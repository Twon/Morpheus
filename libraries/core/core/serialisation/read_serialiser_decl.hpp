#pragma once

#include "core/base/scoped_action.hpp"
#include "core/meta/concepts/constructible.hpp"
#include "core/serialisation/concepts/reader.hpp"

#include <cstddef>
#include <optional>
#include <string_view>
#include <type_traits>

namespace morpheus::serialisation
{

auto makeScopedValue(concepts::Reader auto& reader, std::string_view const key)
{
    return ScopedAction([&reader]{ reader.endValue(); }, [&reader, key]{ reader.beginValue(key); });
}

auto makeScopedSequence(concepts::Reader auto& reader, std::optional<std::size_t> const size = std::nullopt)
{
    return ScopedAction([&reader] { reader.endSequence(); }, [&reader, size] { reader.beginSequence(size); });
}

auto makeScopedComposite(concepts::Reader auto& reader)
{
    return ScopedAction([&reader] { reader.endComposite(); }, [&reader] { reader.beginComposite(); });
}

auto makeScopedNullable(concepts::Reader auto& reader)
{
    return ScopedAction([&reader] { reader.endNullable(); }, [&reader] { return reader.beginNullable(); });
}

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
    ///     Custom deserialise function specialisations should deserialise sub-members via the readers deserialisers
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