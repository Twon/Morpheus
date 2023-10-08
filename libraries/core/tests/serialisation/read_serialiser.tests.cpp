#include "morpheus/core/serialisation/concepts/reader_archtype.hpp"
#include "morpheus/core/serialisation/read_serialiser.hpp"

#include <catch2/catch_all.hpp>

using namespace Catch;

namespace morpheus::serialisation
{

TEST_CASE("Check concepts for read serialisation", "[morpheus.serialisation.read_serialiser.concepts]")
{
    STATIC_REQUIRE(concepts::Reader<concepts::ReaderArchtype>);
}

TEST_CASE("Ensure read serialiser are default constructible where the underlying reader supports it", "[morpheus.serialisation.read_serialiser.default_construction]")
{
    GIVEN("A default constructible reader")
    {
        STATIC_REQUIRE(std::is_default_constructible_v<concepts::ReaderArchtype>);

        WHEN("Ensure read serialiser of given tyoe")
        {
            using ReadSerialiserArchitype = ReadSerialiser<concepts::ReaderArchtype>;
            THEN("Is default construtible")
            {
                STATIC_REQUIRE(std::is_default_constructible_v<ReadSerialiserArchitype>);
            }
        }
    }
    GIVEN("A non-default constructible reader")
    {
        struct NonDefaultConstuctibleReader : concepts::ReaderArchtype
        {
            NonDefaultConstuctibleReader() = delete;
        };
        STATIC_REQUIRE(!std::is_default_constructible_v<NonDefaultConstuctibleReader>);

        WHEN("Ensure read serialiser of given tyoe")
        {
            using NonDefaultConstuctibleReadSerialiserArchitype = ReadSerialiser<NonDefaultConstuctibleReader>;
            THEN("Is default construtible")
            {
                STATIC_REQUIRE(!std::is_default_constructible_v<NonDefaultConstuctibleReadSerialiserArchitype>);
            }
        }
    }
}

TEST_CASE("Ensure read serialiser are forward constructible where the underlying reader supports it", "[morpheus.serialisation.read_serialiser.forwarding_construction]")
{
    GIVEN("A reader with multiple constructors")
    {
        struct MultiConstructorReader : concepts::ReaderArchtype
        {
            MultiConstructorReader() = delete;
            MultiConstructorReader(int, bool) {}
            MultiConstructorReader(int, bool, int, bool);
        };

        STATIC_REQUIRE(std::is_constructible_v<MultiConstructorReader, int, bool>);
        STATIC_REQUIRE(std::is_constructible_v<MultiConstructorReader, int, bool, int, bool>);

        WHEN("Ensure read serialiser of given tyoe")
        {
            using ForwardingSerialiserArchitype = ReadSerialiser<MultiConstructorReader>;
            THEN("Is default construtible")
            {
                STATIC_REQUIRE(!std::is_constructible_v<ForwardingSerialiserArchitype, int>);
                STATIC_REQUIRE(std::is_constructible_v<ForwardingSerialiserArchitype, int, bool>);
                STATIC_REQUIRE(!std::is_constructible_v<ForwardingSerialiserArchitype, int, bool, int>);
                STATIC_REQUIRE(std::is_constructible_v<ForwardingSerialiserArchitype, int, bool, int, bool>);
            }
        }
    }
    GIVEN("A non-default constructible reader")
    {
        STATIC_REQUIRE(!std::is_constructible_v<concepts::ReaderArchtype, int>);
        STATIC_REQUIRE(!std::is_constructible_v<concepts::ReaderArchtype, int, bool>);
        STATIC_REQUIRE(!std::is_constructible_v<concepts::ReaderArchtype, int, bool, int>);
        STATIC_REQUIRE(!std::is_constructible_v<concepts::ReaderArchtype, int, bool, int, bool>);

        WHEN("Ensure read serialiser of given tyoe")
        {
            using ReadSerialiserArchitype = ReadSerialiser<concepts::ReaderArchtype>;
            THEN("Is default construtible")
            {
                STATIC_REQUIRE(!std::is_constructible_v<ReadSerialiserArchitype, int>);
                STATIC_REQUIRE(!std::is_constructible_v<ReadSerialiserArchitype, int, bool>);
                STATIC_REQUIRE(!std::is_constructible_v<ReadSerialiserArchitype, int, bool, int>);
                STATIC_REQUIRE(!std::is_constructible_v<ReadSerialiserArchitype, int, bool, int, bool>);
            }
        }
    }
}

} // namespace morpheus::serialisation
