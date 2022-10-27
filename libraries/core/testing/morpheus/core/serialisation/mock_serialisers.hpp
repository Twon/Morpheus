#pragma once

#include "morpheus/core/serialisation/mock_writer.hpp"
#include "morpheus/core/serialisation/mock_reader.hpp"
#include "morpheus/core/serialisation/read_serialiser.hpp"
#include "morpheus/core/serialisation/write_serialiser.hpp"

namespace morpheus::serialisation
{

using MockWriteSerialiser = WriteSerialiser<mock::Writer>;
//using MockReaderSerialiser = ReadSerialiser<mock::Reader>;

}