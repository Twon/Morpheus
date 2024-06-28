#include "morpheus/core/serialisation/concepts/reader_archtype.hpp"
#include "morpheus/core/serialisation/read_serialiser.hpp"

#include <catch2/catch_all.hpp>

using namespace Catch;

namespace morpheus::serialisation
{

TEST_CASE("Check concepts for read serialisation", "[morpheus.serialisation.read_serialiser.concepts]")
{
    STATIC_REQUIRE(concepts::Reader<concepts::ReaderArchetype>);
}

TEST_CASE("Ensure read serialiser are default constructible where the underlying reader supports it", "[morpheus.serialisation.read_serialiser.default_construction]")
{
    GIVEN("A default constructible reader")
    {
        STATIC_REQUIRE(std::is_default_constructible_v<concepts::ReaderArchetype>);

        WHEN("Ensure read serialiser of given type")
        {
            using ReadSerialiserArchetype = ReadSerialiser<concepts::ReaderArchetype>;
            THEN("Is default construtible")
            {
                STATIC_REQUIRE(std::is_default_constructible_v<ReadSerialiserArchetype>);
            }
        }
    }
    GIVEN("A non-default constructible reader")
    {
        struct NonDefaultConstuctibleReader : concepts::ReaderArchetype
        {
            NonDefaultConstuctibleReader() = delete;
        };
        STATIC_REQUIRE(!std::is_default_constructible_v<NonDefaultConstuctibleReader>);

        WHEN("Ensure read serialiser of given type")
        {
            using NonDefaultConstuctibleReadSerialiserArchetype = ReadSerialiser<NonDefaultConstuctibleReader>;
            THEN("Is default construtible")
            {
                STATIC_REQUIRE(!std::is_default_constructible_v<NonDefaultConstuctibleReadSerialiserArchetype>);
            }
        }
    }
}

TEST_CASE("Ensure read serialiser are forward constructible where the underlying reader supports it", "[morpheus.serialisation.read_serialiser.forwarding_construction]")
{
    GIVEN("A reader with multiple constructors")
    {
        struct MultiConstructorReader : concepts::ReaderArchetype
        {
            MultiConstructorReader() = delete;
            MultiConstructorReader(int, bool) {}
            MultiConstructorReader(int, bool, int, bool){}
        };

        STATIC_REQUIRE(std::is_constructible_v<MultiConstructorReader, int, bool>);
        STATIC_REQUIRE(std::is_constructible_v<MultiConstructorReader, int, bool, int, bool>);

        WHEN("Ensure read serialiser of given type")
        {
            using ForwardingSerialiserArchetype = ReadSerialiser<MultiConstructorReader>;
            THEN("Is default construtible")
            {
                STATIC_REQUIRE(!std::is_constructible_v<ForwardingSerialiserArchetype, int>);
                STATIC_REQUIRE(std::is_constructible_v<ForwardingSerialiserArchetype, int, bool>);
                STATIC_REQUIRE(!std::is_constructible_v<ForwardingSerialiserArchetype, int, bool, int>);
                STATIC_REQUIRE(std::is_constructible_v<ForwardingSerialiserArchetype, int, bool, int, bool>);
            }
        }
    }
    GIVEN("A non-default constructible reader")
    {
        STATIC_REQUIRE(!std::is_constructible_v<concepts::ReaderArchetype, int>);
        STATIC_REQUIRE(!std::is_constructible_v<concepts::ReaderArchetype, int, bool>);
        STATIC_REQUIRE(!std::is_constructible_v<concepts::ReaderArchetype, int, bool, int>);
        STATIC_REQUIRE(!std::is_constructible_v<concepts::ReaderArchetype, int, bool, int, bool>);

        WHEN("Ensure read serialiser of given type")
        {
            using ReadSerialiserArchetype = ReadSerialiser<concepts::ReaderArchetype>;
            THEN("Is default construtible")
            {
                STATIC_REQUIRE(!std::is_constructible_v<ReadSerialiserArchetype, int>);
                STATIC_REQUIRE(!std::is_constructible_v<ReadSerialiserArchetype, int, bool>);
                STATIC_REQUIRE(!std::is_constructible_v<ReadSerialiserArchetype, int, bool, int>);
                STATIC_REQUIRE(!std::is_constructible_v<ReadSerialiserArchetype, int, bool, int, bool>);
            }
        }
    }
}

} // namespace morpheus::serialisation
