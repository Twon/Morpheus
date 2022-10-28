#pragma once

#include "morpheus/core/serialisation/mock/writer.hpp"
#include "morpheus/core/serialisation/mock/reader.hpp"
#include "morpheus/core/serialisation/read_serialiser.hpp"
#include "morpheus/core/serialisation/write_serialiser.hpp"

namespace morpheus::serialisation
{

using MockedWriteSerialiser = WriteSerialiser<mock::Writer>;
using MockedReadSerialiser = ReadSerialiser<mock::Reader>;

}