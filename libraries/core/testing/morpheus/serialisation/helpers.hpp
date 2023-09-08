#include "morpheus/core/serialisation/serialisers.hpp"
#include "morpheus/core/serialisation/write_serialiser.hpp"

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>

namespace morpheus::serialisation::testing
{

std::vector<char> serialise(auto const& value)
{
    std::vector<char> storage;
    boost::iostreams::back_insert_device sink{storage};
    boost::iostreams::stream os{sink};
    BinaryWriteSerialiser serialiser{os};
    serialiser.serialise(value);
    return storage;
}

template <typename T>
T deserialise(std::vector<char> const& value)
{
    boost::iostreams::array_source source{value.data(), value.size()};
    boost::iostreams::stream is{source};
    BinaryReadSerialiser serialiser{is};
    return serialiser.deserialise<T>();
}

template <typename T>
T roundtrip(T const& value)
{
    std::vector<char> binary = serialise(value);
    return deserialise<T>(binary);
}

} // namespace morpheus::serialisation::testing
