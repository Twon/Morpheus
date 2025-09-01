#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/reader.hpp"
#include "morpheus/core/serialisation/concepts/reader_archetype.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/writer.hpp"
#include "morpheus/core/serialisation/concepts/writer_archetype.hpp"
#include "morpheus/core/serialisation/mock/reader.hpp"
#include "morpheus/core/serialisation/mock/serialisers.hpp"
#include "morpheus/core/serialisation/mock/writer.hpp"
#include "morpheus/core/serialisation/read_serialiser.hpp"
// #include "morpheus/core/serialisation/write_serialiser.hpp"

// #include "morpheus/core/serialisation/read_serialiser.hpp"
// #include "morpheus/core/serialisation/serialisers.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace Catch;

namespace morpheus::serialisation
{

TEST_CASE("Verify serialisation concepts", "[morpheus.serialisation.concepts]")
{
    STATIC_REQUIRE(concepts::Reader<concepts::ReaderArchetype>);
    STATIC_REQUIRE(concepts::Writer<concepts::WriterArchetype>);

    STATIC_REQUIRE(concepts::ReadSerialiser<ReadSerialiser<concepts::ReaderArchetype>>);
    STATIC_REQUIRE(concepts::WriteSerialiser<WriteSerialiser<concepts::WriterArchetype>>);
}

TEST_CASE("Verify serialisation mocks adhere to concepts", "[morpheus.serialisation.concepts]")
{
    STATIC_REQUIRE(concepts::Reader<mock::Reader>);
    STATIC_REQUIRE(concepts::Writer<mock::Writer>);

    STATIC_REQUIRE(concepts::ReadSerialiser<MockedReadSerialiser>);
    STATIC_REQUIRE(concepts::WriteSerialiser<MockedWriteSerialiser>);
}

} // namespace morpheus::serialisation
