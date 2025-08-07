#include "morpheus/core/serialisation/write_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/writer_archetype.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace Catch;

namespace morpheus::serialisation
{

TEST_CASE("Check concepts for write serialisation", "[morpheus.serialisation.write_serialiser.concepts]")
{
    STATIC_REQUIRE(concepts::Writer<concepts::WriterArchetype>);
}

TEST_CASE("Ensure write serialiser are default constructible where the underlying writer supports it",
          "[morpheus.serialisation.write_serialiser.default_construction]")
{
    GIVEN("A default constructible writer")
    {
        STATIC_REQUIRE(std::is_default_constructible_v<concepts::WriterArchetype>);

        WHEN("Ensure write serialiser of given type")
        {
            using WriteSerialiserArchetype = WriteSerialiser<concepts::WriterArchetype>;
            THEN("Is default construtible")
            {
                STATIC_REQUIRE(std::is_default_constructible_v<WriteSerialiserArchetype>);
            }
        }
    }
    GIVEN("A non-default constructible writer")
    {
        struct NonDefaultConstuctibleWriter : concepts::WriterArchetype
        {
            NonDefaultConstuctibleWriter() = delete;
        };
        STATIC_REQUIRE(!std::is_default_constructible_v<NonDefaultConstuctibleWriter>);

        WHEN("Ensure write serialiser of given type")
        {
            using NonDefaultConstuctibleWriteSerialiserArchitype = WriteSerialiser<NonDefaultConstuctibleWriter>;
            THEN("Is default construtible")
            {
                STATIC_REQUIRE(!std::is_default_constructible_v<NonDefaultConstuctibleWriteSerialiserArchitype>);
            }
        }
    }
}

TEST_CASE("Ensure write serialiser are forward constructible where the underlying writer supports it",
          "[morpheus.serialisation.write_serialiser.forwarding_construction]")
{
    GIVEN("A writer with multiple constructors")
    {
        struct MultiConstructorWriter : concepts::WriterArchetype
        {
            MultiConstructorWriter() = delete;
            MultiConstructorWriter(int, bool) {}
            MultiConstructorWriter(int, bool, int, bool) {}
        };

        STATIC_REQUIRE(std::is_constructible_v<MultiConstructorWriter, int, bool>);
        STATIC_REQUIRE(std::is_constructible_v<MultiConstructorWriter, int, bool, int, bool>);

        WHEN("Ensure write serialiser of given type")
        {
            using ForwardingSerialiserArchetype = WriteSerialiser<MultiConstructorWriter>;
            THEN("Is default construtible")
            {
                STATIC_REQUIRE(!std::is_constructible_v<ForwardingSerialiserArchetype, int>);
                STATIC_REQUIRE(std::is_constructible_v<ForwardingSerialiserArchetype, int, bool>);
                STATIC_REQUIRE(!std::is_constructible_v<ForwardingSerialiserArchetype, int, bool, int>);
                STATIC_REQUIRE(std::is_constructible_v<ForwardingSerialiserArchetype, int, bool, int, bool>);
            }
        }
    }
    GIVEN("A non-default constructible writer")
    {
        STATIC_REQUIRE(!std::is_constructible_v<concepts::WriterArchetype, int>);
        STATIC_REQUIRE(!std::is_constructible_v<concepts::WriterArchetype, int, bool>);
        STATIC_REQUIRE(!std::is_constructible_v<concepts::WriterArchetype, int, bool, int>);
        STATIC_REQUIRE(!std::is_constructible_v<concepts::WriterArchetype, int, bool, int, bool>);

        WHEN("Ensure write serialiser of given type")
        {
            using WriteSerialiserArchetype = WriteSerialiser<concepts::WriterArchetype>;
            THEN("Is default construtible")
            {
                STATIC_REQUIRE(!std::is_constructible_v<WriteSerialiserArchetype, int>);
                STATIC_REQUIRE(!std::is_constructible_v<WriteSerialiserArchetype, int, bool>);
                STATIC_REQUIRE(!std::is_constructible_v<WriteSerialiserArchetype, int, bool, int>);
                STATIC_REQUIRE(!std::is_constructible_v<WriteSerialiserArchetype, int, bool, int, bool>);
            }
        }
    }
}

} // namespace morpheus::serialisation
