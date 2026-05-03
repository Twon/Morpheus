#pragma once

#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"
#include "morpheus/core/serialisation/fundamentals.hpp"

namespace morpheus::serialisation
{

namespace detail
{

inline namespace defaults
{

template <concepts::WriteSerialiser Serialiser, concepts::WriteSerialisableInsrusive Type>
auto serialise(Serialiser& serialiser, Type const& value) -> void
{
    value.serialise(serialiser);
}

template <concepts::ReadSerialiser Serialiser, concepts::ReadSerialisableInsrusive Type>
auto deserialise(Serialiser& serialiser, std::type_identity<Type>) -> Type
{
    Type value;
    serialiser.reader().beginComposite();
    value.deserialise(serialiser);
    serialiser.reader().endComposite();
    return value;
}

template <concepts::ReadSerialiser Serialiser, concepts::ReadSerialisableInsrusive Type>
auto deserialise_to(Serialiser& serialiser, Type& value) -> void
{
    serialiser.reader().beginComposite();
    value.deserialise(serialiser);
    serialiser.reader().endComposite();
}

} // namespace defaults

/// \struct serialise_fn
///     Customisation point functor for serialising a value.
struct serialise_fn
{
    /// Serialise a value using the provided serialiser.
    /// \tparam Serialiser The type of the serialiser to use.
    /// \tparam Type The type of the value to serialise.
    /// \param serialiser The serialiser to use for serialisation.
    /// \param value The value to serialise.
    template <concepts::WriteSerialiser Serialiser, typename Type>
    void operator()(Serialiser& serialiser, Type const& value) const
    {
        using detail::serialise;
        serialise(serialiser, value);
    }
};

template <concepts::ReadSerialiser Serialiser, typename Type>
auto adl_deserialise(Serialiser& s, std::type_identity<Type> type) -> Type
{
    using detail::deserialise;
    return deserialise(s, type);
}

template <concepts::ReadSerialiser Serialiser, typename Type>
auto adl_deserialise_to(Serialiser& s, Type&& value) -> void
{
    using detail::deserialise_to;
    return deserialise_to(s, std::forward<Type>(value));
}

/// \struct deserialise_fn
///     Customisation point functor for deserialising a value.
struct deserialise_fn
{
    /// Deserialise a value using the provided serialiser.
    /// \tparam Serialiser The type of the serialiser to use.
    /// \tparam Type The type of the value to deserialise.
    /// \param serialiser The serialiser to use for deserialisation.
    /// \return The deserialised value.
    template <concepts::ReadSerialiser Serialiser, typename Type>
    requires requires(Serialiser& s) { adl_deserialise(s, std::type_identity<Type>{}); }
    auto operator()(Serialiser& serialiser) const -> Type
    {
        using detail::deserialise;
        return deserialise(serialiser, std::type_identity<Type>{});
    }

    /// Deserialise into a value using the provided serialiser.
    /// \tparam Serialiser The type of the serialiser to use.
    /// \tparam Type The type of the value to deserialise.
    /// \param[in] serialiser The serialiser to use for deserialisation.
    /// \param[out] value The value to deserialise into.
    template <concepts::ReadSerialiser Serialiser, typename Type>
    requires requires(Serialiser& s, Type&& v) { adl_deserialise_to(s, std::forward<Type>(v)); }
    void operator()(Serialiser& serialiser, Type&& value) const
    {
        using detail::deserialise_to;
        deserialise_to(serialiser, std::forward<Type>(value));
    }
};

} // namespace detail

namespace defaults = detail::defaults;

// global customisation point objects serialisation::serialise() and serialisation::deserialise()
inline constexpr detail::serialise_fn serialise{};
inline constexpr detail::deserialise_fn deserialise{};
} // namespace morpheus::serialisation
