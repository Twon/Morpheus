#pragma once

// IWYU pragma: always_keep
#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/core/meta/concepts/string.hpp"
#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"

#include <iterator>
#include <type_traits>
#include <version>

namespace morpheus::serialisation::detail
{

/// To enable serialisation for any type meeting the concept of a range then enable serialisation by specialising and enabling this value.
template <typename T>
inline constexpr bool isEnabledForRangeSerialisation = false;

/// \concept IsRange
///   For the purpose of serialisation of ranges we want to know that a given type is range, but also that we explicitly want to opt in as a Range
///   compatible type.  This is because certain type which already count as ranges are already handled within the framework, mainly strings.
///   Rather than special case ignoring strings an potentially other types the user must opt in by specialising \ref isEnabledForRangeSerialisation
///   for types that should be included for range support.
template <typename T>
concept IsRange = conf::ranges::range<T> and isEnabledForRangeSerialisation<T>;

template <concepts::WriteSerialiser Serialiser>
void serialise(Serialiser& serialiser, IsRange auto const& range)
{
    serialiser.writer().beginSequence(conf::ranges::size(range));
    conf::ranges::for_each(range, [&serialiser](auto const& element) { serialiser.serialise(element); });
    serialiser.writer().endSequence();
}

template <typename T>
concept IsMapLike = requires {
    typename T::key_type;
    typename T::mapped_type;
};

template <typename T>
struct RangeDeserialiseValue
{
    using type = conf::ranges::range_value_t<T>;
};

template <IsMapLike T>
struct RangeDeserialiseValue<T>
{
    using type = std::pair<typename T::key_type, typename T::mapped_type>;
};

template <concepts::ReadSerialiser Serialiser, IsRange T>
void deserialise(Serialiser& serialiser, T& range)
{
    using ValueType = typename RangeDeserialiseValue<T>::type;

    auto seq = serialiser.template sequence<ValueType>();

#if defined(__cpp_lib_containers_ranges) && __cpp_lib_containers_ranges >= 202202L
    if constexpr (requires { range.assign_range(std::move(seq)); })
    {
        range.assign_range(std::move(seq));
    }
    else
#endif
    {
        if constexpr (requires { range.clear(); })
        {
            range.clear();
        }

        if constexpr (requires { range.push_back(std::declval<ValueType>()); })
        {
            conf::ranges::copy(seq, std::back_inserter(range));
        }
        else
        {
            conf::ranges::copy(seq, std::inserter(range, range.end()));
        }
    }
}

template <concepts::ReadSerialiser Serialiser, IsRange T>
T deserialise(Serialiser& serialiser, std::type_identity<T>)
{
    using ValueType = typename RangeDeserialiseValue<T>::type;

#if defined(__cpp_lib_ranges_to_container) && __cpp_lib_ranges_to_container >= 202202L
    return conf::ranges::to<T>(serialiser.template sequence<ValueType>());
#elif defined(__cpp_lib_containers_ranges) && __cpp_lib_containers_ranges >= 202202L
    return T(std::from_range, serialiser.template sequence<ValueType>());
#else
    T range;
    serialiser.deserialise(range);
    return range;
#endif
}

} // namespace morpheus::serialisation::detail
