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

auto makeScopedSequence(concepts::Reader auto& reader, std::optional<std::size_t> const size = std::nullopt)
{
    return ScopedAction([&reader, size] { reader.beginSequence(); }, [&reader] { reader.endSequence(); } );
}

auto makeScopedComposite(concepts::Reader auto& reader)
{
    return ScopedAction([&reader] { reader.beginComposite(); }, [&reader] { reader.endComposite(); } );
}

auto makeScopedNullable(concepts::Reader auto& reader)
{
    return ScopedAction([&reader] { return reader.beginNullable(); }, [&reader] { reader.endNullable(); } );
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

#if (__cpp_explicit_this_parameter >= 202110)
    template<typename Self>
    [[nodiscard]] auto& reader(this Self&& self) noexcept { return self.mReader; }
#else
    [[nodiscard]] ReaderType& reader() noexcept { return mReader; }
    [[nodiscard]] ReaderType const& reader() const noexcept { return mReader; }
#endif // (__cpp_explicit_this_parameter >= 202110)

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

    /// Deserialise a sequence of values
    /// \tparam T The underlying type of sequence to deserialise.
    /// \param[in] size The number of entries in the sequence to serialise.
    /// \param[in] f The command deserialising the sequence of values.
    template<typename T>
    [[nodiscard]] T deserialise(std::size_t size, std::invocable auto f);

    /// Deserialise a related set of values in a composite.
    /// \tparam T The underlying type of composite to deserialise.
    /// \param[in] f The command deserialising the composite values.
    template<typename T>
    [[nodiscard]] T deserialise(std::invocable auto f);

    /// Deserialise a nullable value
    /// \tparam T The underlying type of nullable to deserialise.
    /// \param[in] null If the nullable value is null or set.
    /// \param[in] f The command deserialising the nullable values.
    template<typename T>
    [[nodiscard]] T deserialise(bool const null, std::invocable auto f = []{});
    ///@}
private:
    ReaderType mReader;
};

}