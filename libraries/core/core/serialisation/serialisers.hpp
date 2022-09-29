#pragma once

#include "core/base/platform.hpp"
#include "core/serialisation/json_writer.hpp"
#include "core/serialisation/json_reader.hpp"
#include "core/serialisation/serialise.hpp"
#include "core/serialisation/read_serialiser.hpp"
#include "core/serialisation/write_serialiser.hpp"

namespace morpheus::serialisation
{

using JsonWriteSerialiser = WriteSerialiser<JsonWriter>;

}