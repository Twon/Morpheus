#pragma once

#include "core/serialisation/concepts/write_serialiser.hpp"
#include "core/serialisation/concepts/write_serialisable.hpp"
#include "core/serialisation/dispatch.hpp"
#include "core/meta/concepts/aggregate.hpp"

#include <boost/pfr/ops.hpp>
#include <boost/pfr/tuple_size.hpp>

namespace morpheus::serialisation
{

/// \var delegateAggregateSerialisation
///     Template variable to be specialised to opt-in to aggregate serialisaion.
/// \tparam T The type specialising to decide if to opt-in to aggregate serialisaion.
template<typename T>
inline constexpr bool delegateAggregateSerialisation = false;

/// \concept DelegatedAggregateSerialisation
/// 
template<typename T>
concept DelegatedAggregateSerialisation = delegateAggregateSerialisation<T>;

/// \concept SerialisableAggregate
///     Constrains a type to aggregate that opts into automatic serialisation.
template<typename T>
concept SerialisableAggregate = meta::concepts::Aggregate<T> and DelegatedAggregateSerialisation<T>;

/// Opt in serialisation for aggregates.  Like pair and tuple it serialises as a sequence without the field key
/// as fields can only be accessed by the underlying field value.  Hense if you want an aggregate with named
/// field then this should have its one specialised serialisation method
template<typename Serialiser, SerialisableAggregate AggregateType>
void serialise(Serialiser& s, AggregateType const& value, DispatchStrong)
{
    s.writer().beginSequence(boost::pfr::tuple_size<AggregateType>::value);
    boost::pfr::for_each_field(value, [&](const auto& field) {
        serialise(s, field, DispatchSelect<decltype(field)>());
    });
    s.writer().endSequence();
}

}