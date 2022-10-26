#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/reader.hpp"
#include "morpheus/core/serialisation/concepts/reader_archtype.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/writer.hpp"
#include "morpheus/core/serialisation/concepts/writer_archtype.hpp"

#include "morpheus/core/serialisation/read_serialiser.hpp"
//#include "morpheus/core/serialisation/write_serialiser.hpp"

//#include "morpheus/core/serialisation/read_serialiser.hpp"
//#include "morpheus/core/serialisation/serialisers.hpp"

#include <catch2/catch_all.hpp>

using namespace Catch;

namespace morpheus::serialisation
{

TEST_CASE("Verify serialisation concepts", "[morpheus.serialisation.concepts]")
{
    STATIC_REQUIRE(concepts::Reader<concepts::ReaderArchtype>);
    STATIC_REQUIRE(concepts::Writer<concepts::WriterArchtype>);

    STATIC_REQUIRE(concepts::ReadSerialiser<ReadSerialiser<concepts::ReaderArchtype>>);
    STATIC_REQUIRE(concepts::WriteSerialiser<WriteSerialiser<concepts::WriterArchtype>>);
}

}