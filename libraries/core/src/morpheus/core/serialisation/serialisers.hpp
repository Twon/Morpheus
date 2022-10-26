#pragma once

#include "morpheus/core/base/platform.hpp"
#include "morpheus/core/serialisation/json_writer.hpp"
#include "morpheus/core/serialisation/json_reader.hpp"
#include "morpheus/core/serialisation/serialise.hpp"
#include "morpheus/core/serialisation/read_serialiser.hpp"
#include "morpheus/core/serialisation/write_serialiser.hpp"

namespace morpheus::serialisation
{

using JsonWriteSerialiser = WriteSerialiser<JsonWriter>;
using JsonReaderSerialiser = ReadSerialiser<JsonReader>;

}