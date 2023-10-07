#include "morpheus/core/serialisation/adapters/std/monostate.hpp"
#include "morpheus/core/serialisation/mock/serialisers.hpp"
#include "morpheus/core/serialisation/mock/writer.hpp"

#include <catch2/catch_all.hpp>
#include <gmock/gmock.h>

#include <utility>

namespace morpheus::serialisation
{

using namespace ::testing;

TEST_CASE("Verify serialisation of std::monostate", "[morpheus.serialisation.monostate.serialise]")
{
    GIVEN("A std::monostate holding a value")
    {
        std::monostate value{};

        THEN("Expect the following sequence of operations on the underlying writer")
        {
            InSequence seq;
            MockedWriteSerialiser serialiser;
            EXPECT_CALL(serialiser.writer(), beginComposite()).Times(1);
            EXPECT_CALL(serialiser.writer(), endComposite()).Times(1);

            WHEN("Serialising a std::monostate") { serialiser.serialise(value); }
        }
    }
}

TEST_CASE("Verify deserialisation of std::monostate", "[morpheus.serialisation.monostate.deserialise]")
{
    GIVEN("A serialiser which can track expected calls")
    {
        THEN("Expect the following sequence of operations on the underlying reader")
        {
            MockedReadSerialiser serialiser;
            EXPECT_CALL(serialiser.reader(), beginComposite()).Times(1);
            EXPECT_CALL(serialiser.reader(), endComposite()).Times(1);

            WHEN("Deserialising a std::monostate") { auto const value = serialiser.deserialise<std::monostate>(); }
        }
    }
}

} // namespace morpheus::serialisation
