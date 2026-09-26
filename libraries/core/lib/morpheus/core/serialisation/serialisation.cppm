module;

#include <morpheus/core/serialisation/concepts/hexable.hpp>
#include <morpheus/core/serialisation/concepts/read_serialisable.hpp>
#include <morpheus/core/serialisation/concepts/read_serialiser.hpp>
#include <morpheus/core/serialisation/concepts/reader.hpp>
#include <morpheus/core/serialisation/concepts/reader_archetype.hpp>
#include <morpheus/core/serialisation/concepts/write_archetype.hpp>
#include <morpheus/core/serialisation/concepts/write_serialisable.hpp>
#include <morpheus/core/serialisation/concepts/write_serialiser.hpp>
#include <morpheus/core/serialisation/concepts/writer.hpp>

export module morpheus.core:serialisation;

export namespace morpheus::core::serialisation
{

using morpheus::serialisation::concepts::Hexable;
using morpheus::serialisation::concepts::Reader;
using morpheus::serialisation::concepts::ReaderArchetype;
using morpheus::serialisation::concepts::ReadSerialisable;
using morpheus::serialisation::concepts::ReadSerialiser;
using morpheus::serialisation::concepts::WriteArchetype;
using morpheus::serialisation::concepts::Writer;
using morpheus::serialisation::concepts::WriteSerialisable;
using morpheus::serialisation::concepts::WriteSerialiser;

} // namespace morpheus::core::serialisation
