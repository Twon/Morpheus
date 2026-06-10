#pragma once

#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/core/serialisation/adapters/std/ranges.hpp"
#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"

#include <boost/circular_buffer.hpp>

#include <type_traits>

namespace morpheus::serialisation::detail
{

template <typename T, typename Alloc>
inline constexpr bool
    isEnabledForRangeSerialisation<conf::ranges::subrange<boost::cb_details::iterator<boost::circular_buffer<T, Alloc>, boost::cb_details::const_traits<Alloc>>,
                                                          boost::cb_details::iterator<boost::circular_buffer<T, Alloc>, boost::cb_details::const_traits<Alloc>>,
                                                          conf::ranges::subrange_kind::sized>> = true;

template <concepts::WriteSerialiser Serialiser, typename T, typename Allocator>
void serialise(Serialiser& serialiser, boost::circular_buffer<T, Allocator> const& buffer)
{
    serialiser.writer().beginComposite();
    serialiser.serialise("capacity", static_cast<std::uint64_t>(buffer.capacity()));
    serialiser.serialise("values", conf::ranges::subrange(buffer.begin(), buffer.end()));
    serialiser.writer().endComposite();
}

template <concepts::ReadSerialiser Serialiser, typename T, typename Allocator>
boost::circular_buffer<T, Allocator> deserialise(Serialiser& serialiser, std::type_identity<boost::circular_buffer<T, Allocator>>)
{
    boost::circular_buffer<T, Allocator> buffer;
    serialiser.reader().beginComposite();
    buffer.set_capacity(serialiser.template deserialise<std::uint64_t>("capacity"));
    conf::ranges::copy(serialiser.template sequence<T>("values"), std::back_inserter(buffer));
    serialiser.reader().endComposite();
    return buffer;
}

} // namespace morpheus::serialisation::detail
