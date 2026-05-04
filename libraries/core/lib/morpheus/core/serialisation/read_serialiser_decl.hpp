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
    return ScopedAction([&reader, key] { reader.beginValue(key); }, [&reader] { reader.endValue(); });
}

auto makeScopedSequence(concepts::Reader auto& reader, std::optional<std::size_t> const = std::nullopt)
{
    return ScopedAction([&reader] { return reader.beginSequence(); }, [&reader] { reader.endSequence(); });
}

auto makeScopedComposite(concepts::Reader auto& reader)
{
    return ScopedAction([&reader] { reader.beginComposite(); }, [&reader] { reader.endComposite(); });
}

auto makeScopedNullable(concepts::Reader auto& reader)
{
    return ScopedAction([&reader] { return reader.beginNullable(); }, [&reader] { reader.endNullable(); });
}

/// \class ReadSerialiser
/// \tparam ReaderType The type of underlying reader for serialisation.
template <concepts::Reader ReaderType>
class ReadSerialiser
{
public:
    using Reader = ReaderType;

    /// Constructs a ReadSerialiser when the underlying reader supports default construction.
    template <meta::concepts::DefaultConstructible T = ReaderType>
    explicit ReadSerialiser() noexcept(meta::concepts::DefaultNothrowConstructible<T>)
    {}

    explicit ReadSerialiser(ReaderType&& reader) noexcept
        : mReader(std::move(reader))
    {}

    /// Constructs a ReadSerialiser with the provided arguments when the underlying reader supports construction
    /// with those arguments.
    /// \tparam Args The types of the arguments to forward to the reader's constructor.
    /// \param tag The tag to indicate that the reader should be constructed in-place.
    /// \param args The arguments to forward to the reader's constructor.
    template <typename... Args>
    requires(std::is_constructible_v<ReaderType, Args...>)
    explicit ReadSerialiser([[maybe_unused]] std::in_place_t tag, Args&&... args) noexcept(meta::concepts::NothrowConstructible<ReaderType, Args...>)
        : mReader(std::forward<Args>(args)...)
    {}

#if (__cpp_explicit_this_parameter >= 202110)
    /// Access the underlying reader.
    // template <typename Self>
    [[nodiscard]] auto reader(this auto&& self) noexcept -> decltype(auto) { return std::forward_like<decltype(self)>(self.mReader); }
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
    template <typename T>
    [[nodiscard]] auto deserialise() -> T;

    /// Deserialise a single value with an allocator.
    /// \tparam T The underlying type of value to deserialise.
    /// \tparam Allocator The type of the allocator to use.
    /// \param[in] alloc The allocator to use.
    /// \return The deserialises value.
    // template <typename T, typename Allocator>
    //[[nodiscard]] T deserialise(Allocator const& alloc);

    /// Deserialise to a non-default construtible single value
    /// \tparam T The underlying type of value to deserialise.
    /// \param[out] The deserialises value.
    template <typename T>
    auto deserialise(T& value) -> void;

    /// Deserialise a key value pair
    /// \tparam T The underlying type of value to deserialise.
    /// \param[in] key The key to serialise.
    /// \return The deserialises value.
    template <typename T>
    [[nodiscard]] auto deserialise(std::string_view const key) -> T;

    /// Deserialise a sequence of values
    /// \tparam T The underlying type of values to deserialise.
    /// \return A generator yielding the deserialised values.
    template <typename T>
    [[nodiscard]] auto sequence() -> concurrency::Generator<T>;

    /// Deserialise a sequence of values with an allocator.
    /// \tparam T The underlying type of values to deserialise.
    /// \tparam Allocator The type of the allocator to use for internal buffers if needed.
    /// \param[in] alloc The allocator to use.
    /// \return A generator yielding the deserialised values.
    // template <typename T>
    //[[nodiscard]] concurrency::Generator<T> sequence(Allocator const& alloc);

    /// Deserialise a named sequence of values
    /// \tparam T The underlying type of values to deserialise.
    /// \param[in] key The key to serialise.
    /// \return A generator yielding the deserialised values.
    template <typename T>
    [[nodiscard]] auto sequence(std::string_view const key) -> concurrency::Generator<T>;
    ///@}
private:
    ReaderType mReader; ///< The underlying reading for serialising fundamental types.
};

} // namespace morpheus::serialisation
