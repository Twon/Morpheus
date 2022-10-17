#pragma once

#include "core/serialisation/concepts/read_serialiser.hpp"
#include "core/serialisation/concepts/read_serialisable.hpp"
#include "core/serialisation/concepts/write_serialiser.hpp"
#include "core/serialisation/concepts/write_serialisable.hpp"
#include "core/serialisation/fundamentals.hpp"

namespace morpheus::serialisation
{

namespace detail {

inline namespace defaults {

template<concepts::WriteSerialiser Serialiser, concepts::WriteSerialisableInsrusive Type>
void serialise(Serialiser& serialiser, Type const& value)
{
    value.serialise(serialiser);
}

template<concepts::ReadSerialiser Serialiser, concepts::ReadSerialisableInsrusive Type>
auto deserialise(Serialiser& serialiser)
{
    Type value;
    serialiser.reader().beginComposite();
    value.deserialise(serialiser);
    serialiser.reader().endComposite();
    return value;
}

}

struct serialise_fn {
    template<concepts::WriteSerialiser Serialiser, typename Type>
    void operator() (Serialiser& serialiser, Type const& value) const
    {
        using detail::serialise;
        serialise(serialiser, value);
    }
};

struct deserialise_fn {
    template<concepts::ReadSerialiser Serialiser, concepts::ReadSerialisable Type>
    auto operator() (Serialiser& serialiser) const
    {
        using detail::serialise;
        return deserialise<Serialiser, Type>(serialiser);
    }
};

}

namespace defaults = detail::defaults;

// global customisation point objects serialisation::serialise() and serialisation::deserialise()
inline detail::serialise_fn const serialise{};
inline detail::deserialise_fn const deserialise{};

}